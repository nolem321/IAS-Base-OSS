/*
 * File: IAS-CommonLib/src/commonlib/net/ssl/SSLException.cpp
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
#include "SSLException.h"
#include <commonlib/logger/logger.h>

#include <openssl/ssl.h>
#include "Environment.h"

namespace IAS {
namespace Net {
namespace SSL {


/*************************************************************************/
SSLException::SSLException(){
	IAS_TRACER;
	Environment::GetInstance()->printErrors();
}
/*************************************************************************/
SSLException::SSLException(const String& strInfo):
	Exception(strInfo){
	Environment::GetInstance()->printErrors();
}
/*************************************************************************/
SSLException::~SSLException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* SSLException::getName(){
	IAS_TRACER;
	return "SSLException";
}

/*************************************************************************/
}
}
}
/* namespace IAS */
