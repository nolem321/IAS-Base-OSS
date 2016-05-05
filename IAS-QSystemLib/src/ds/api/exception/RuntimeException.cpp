/*
 * File: IAS-QSystemLib/src/ds/api/exception/RuntimeException.cpp
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
#include "RuntimeException.h"

#include <commonlib/commonlib.h>

namespace IAS{
namespace DS{
namespace API{

/*************************************************************************/
RuntimeException::RuntimeException(){
	IAS_TRACER;		
}
/*************************************************************************/
RuntimeException::RuntimeException(const String& strItemName){
	IAS_TRACER;
	this->setInfo(strItemName);
}
/*************************************************************************/
RuntimeException::~RuntimeException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* RuntimeException::getName(){
	IAS_TRACER;
	return "RuntimeException";
}

/*************************************************************************/
}
}
} /* namespace IAS */
