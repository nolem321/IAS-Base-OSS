/*
 * File: IAS-QSystemLib/src/qs/workers/proc/dict/Dictionary.cpp
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
#include "Dictionary.h"


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Dict {

/*************************************************************************/
Dictionary::Dictionary(){
	IAS_TRACER;
}

/*************************************************************************/
Dictionary::~Dictionary() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Dictionary::setValue(const String& strKey, DM::DataObject* dm){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	hmValues[strKey]=dm;
}
/*************************************************************************/
DM::DataObject* Dictionary::getValue(const String& strKey){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmValues.count(strKey) == 0)
		IAS_THROW(ItemNotFoundException(String("Dictionary value not found for:"+strKey)));

	return hmValues.at(strKey);
}
/*************************************************************************/

}
}
}
}
}
