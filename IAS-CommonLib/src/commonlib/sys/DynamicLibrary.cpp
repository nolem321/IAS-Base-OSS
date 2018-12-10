/*
 * File: IAS-CommonLib/src/commonlib/sys/DynamicLibrary.cpp
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
#include "DynamicLibrary.h"

#include "../logger/logger.h"
#include "../memory/memory.h"

namespace IAS {
namespace SYS {

/*************************************************************************/
DynamicLibrary::DynamicLibrary(const String& strFileName, int  iMode):
		pHandle(NULL),
		strFileName(strFileName){
	IAS_TRACER;

	this->strFileName=strFileName;

	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"["<<strFileName<<"]:"<<iMode);

	if( (pHandle=dlopen(strFileName.c_str(), iMode)) == NULL){
    String strError(dlerror());
	  IAS_LOG(IAS::LogLevel::INSTANCE.isError(),strError);
  	IAS_THROW(IAS::Exception(strError));
  }

	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),(void*)pHandle);
}

/*************************************************************************/
DynamicLibrary::~DynamicLibrary() throw(){
	IAS_TRACER;
	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"["<<strFileName<<"]");
	if(pHandle != NULL){
		if(dlclose(pHandle) != 0)
			IAS_LOG(IAS::LogLevel::INSTANCE.isError(),"["<<strFileName<<"]: dlclose="<<dlerror());
	}
}

/*************************************************************************/
void* DynamicLibrary::getSymbol(const String& strSymbolName){
	IAS_TRACER;

	void *pResult = NULL;

	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"["<<strFileName<<"]:["<<strSymbolName<<"]");

	if( (pResult=dlsym(pHandle, strSymbolName.c_str())) == NULL)
		IAS_THROW(IAS::Exception(dlerror()));

	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"["<<strFileName<<"]:["<<strSymbolName<<"]="<<(void*)pResult);

	return pResult;
}

/*************************************************************************/
}
}
