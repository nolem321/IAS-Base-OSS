/*
 * File: IAS-CommonLib/src/commonlib/sys/DynamicLibraryStore.cpp
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
#include "DynamicLibraryStore.h"
#include "DynamicLibrary.h"
#include <commonlib/logger/logger.h>


namespace IAS {
namespace SYS {

/*************************************************************************/
DynamicLibraryStore::DynamicLibraryStore(){
	IAS_TRACER;
}

/*************************************************************************/
DynamicLibraryStore::~DynamicLibraryStore(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::SYS::DynamicLibrary *DynamicLibraryStore::getLibrary(const String& strName){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmLibraries.count(strName) == 0){
		hmLibraries[strName]=IAS_DFT_FACTORY<SYS::DynamicLibrary>::Create(strName);
	}

	return hmLibraries.at(strName);
}
/*************************************************************************/
}
}
