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
Dictionary* DictionaryStore::lookup(const String& strDictionary){
	IAS_TRACER;

	if(hmDictionaries.count(strDictionary)==0)
		hmDictionaries[strDictionary]=IAS_DFT_FACTORY<Dictionary>::Create();

	return hmDictionaries[strDictionary];
}
/*************************************************************************/
}
}
}
}
}
