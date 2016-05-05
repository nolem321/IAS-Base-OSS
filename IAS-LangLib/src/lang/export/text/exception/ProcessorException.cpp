/*
 * File: IAS-LangLib/src/lang/interpreter/text/exception/ProcessorException.cpp
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
#include "ProcessorException.h"

#include<lang/log/LogLevel.h>

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {

/*************************************************************************/
ProcessorException::ProcessorException(){
	IAS_TRACER;
}
/*************************************************************************/
ProcessorException::ProcessorException(const String& strInfo){
	IAS_TRACER;
	setInfo(strInfo);
}
/*************************************************************************/
ProcessorException::~ProcessorException() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const char* ProcessorException::getName(){
	IAS_TRACER;
	return "ProcessorException";
}
/*************************************************************************/
}
}
}
}
