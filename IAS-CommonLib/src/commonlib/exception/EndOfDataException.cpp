/*
 * File: IAS-CommonLib/src/commonlib/exception/EndOfDataException.cpp
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
#include "EndOfDataException.h"

#include "../memory/memory.h"
#include "../logger/logger.h"

#include "../memory/memory.h"
#include "../logger/logger.h"
#include "../ui/UserMessage.h"

#include <errno.h>
#include <string.h>

namespace IAS{

/*************************************************************************/
EndOfDataException::EndOfDataException(){
	IAS_TRACER;
}

/*************************************************************************/
EndOfDataException::EndOfDataException(const String& strInfo){

	IAS_TRACER;
	setInfo(strInfo);
}


/*************************************************************************/
EndOfDataException::~EndOfDataException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* EndOfDataException::getName(){
	IAS_TRACER;
	return "EndOfDataException";
}

/*************************************************************************/
} /* namespace IAS */
