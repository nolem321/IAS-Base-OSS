/*
 * File: IAS-CommonLib/src/commonlib/exception/SystemException.cpp
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
#include "SystemException.h"

#include "../memory/memory.h"
#include "../logger/logger.h"

#include <errno.h>
#include <string.h>

namespace IAS{

/*************************************************************************/
SystemException::SystemException(int iErrno){
	IAS_TRACER;
	StringStream ss;
	ss<<errno<<":"<<strerror(iErrno);
	setInfo(ss.str());
}
/*************************************************************************/
SystemException::SystemException(){
	IAS_TRACER;	
	StringStream ss;
	ss<<errno<<":"<<strerror(errno);
	setInfo(ss.str());
}
/*************************************************************************/
SystemException::SystemException(const String& strInfo, int iErrno){
	IAS_TRACER;
	StringStream ss;
	ss<<strInfo<<":";

	if(iErrno != -1)
		ss<<errno<<":"<<strerror(iErrno);
	else
		ss<<errno<<":"<<strerror(errno);

	setInfo(ss.str());
}

/*************************************************************************/
SystemException::~SystemException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* SystemException::getName(){
	IAS_TRACER;
	return "SystemException";
}

/*************************************************************************/
} /* namespace IAS */
