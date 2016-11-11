/*
 * File: IAS-QSystemLib/src/qs/workers/proc/dict/DictionaryStore.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "DictionaryStore.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Dict {

/*************************************************************************/
DictionaryStore::DictionaryStore(){
	IAS_TRACER;
}

/*************************************************************************/
DictionaryStore::~DictionaryStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DM::DataObject* DictionaryStore::getValue(const String& strDictionary, const String& strKey, unsigned int iTimeoutMS){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	return lookup(strDictionary,iTimeoutMS)->getValue(strKey)->duplicate();
}
/*************************************************************************/
Dictionary* DictionaryStore::lookup(const String& strDictionary, unsigned int iTimeoutMS){
	IAS_TRACER;

	if(hmDictionaries.count(strDictionary) == 0){

		unsigned int iStartTimeMS = TypeTools::GetTimeMS();

		do{

			if(!iTimeoutMS)
				IAS_THROW(ItemNotFoundException("Dictionary: "+strDictionary));

			Thread::Cancellation tc(true);

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Waiting for dictionary:"<<strDictionary<<", timeout:"<< iTimeoutMS);

			if(!mutex.wait(cndWaitForDictionary, iTimeoutMS))
				IAS_THROW(ItemNotFoundException("Timedout when waiting for dictionary: "+strDictionary));

			unsigned int iTimeMS = TypeTools::GetTimeMS();

			if(iTimeMS - iStartTimeMS > iTimeoutMS)
				iTimeoutMS = 0;
			else
				iTimeoutMS = iTimeoutMS - (iTimeMS - iStartTimeMS);



		}while(hmDictionaries.count(strDictionary) == 0);

	}


	if(hmDictionaries.count(strDictionary) == 0)
		IAS_THROW(ItemNotFoundException("Timed out when waiting for dictionary: "+strDictionary));

	return hmDictionaries[strDictionary];
}
/*************************************************************************/
void DictionaryStore::create(const workers::dict::Dictionary* dmDictionary){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	String strDictionary(dmDictionary->getName());


	//TODO clear & swap
	//if(hmDictionaries.count(strDictionary)==0)

	hmDictionaries[strDictionary]=IAS_DFT_FACTORY<Dictionary>::Create(strDictionary);

	Dictionary *pDictionary = hmDictionaries.at(strDictionary);

	const workers::dict::Ext::ItemList& lstItems(dmDictionary->getItemsList());

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"New dictionary:"<<strDictionary<<", no. of items: "<<lstItems.size());

	for(int iIdx=0; iIdx < lstItems.size(); iIdx++){
		const workers::dict::Item *dmItem(lstItems.at(iIdx));

		pDictionary->setValue(dmItem->getKey(), dmItem->getValue()->duplicate());
	}

	cndWaitForDictionary.broadcast();
}
/*************************************************************************/
}
}
}
}
}
