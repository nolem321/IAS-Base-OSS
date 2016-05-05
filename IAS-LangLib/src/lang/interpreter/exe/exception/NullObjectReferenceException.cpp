/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/NullObjectReferenceException.cpp
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
#include "NullObjectReferenceException.h"

#include<lang/log/LogLevel.h>

#include <org/invenireaude/lang/builtin/NullObjectReferenceException.h>

using namespace org::invenireaude;

namespace IAS{
namespace Lang {
namespace Interpreter{
namespace Exe{
/*************************************************************************/
NullObjectReferenceException::NullObjectReferenceException(const String& strInfo):
		InterpreterRuntimeException(
				lang::builtin::DataFactory::GetInstance()->getNullObjectReferenceExceptionType()->
				createNullObjectReferenceException(), strInfo){

	IAS_TRACER;
}
/*************************************************************************/
NullObjectReferenceException::~NullObjectReferenceException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* NullObjectReferenceException::getName(){
	IAS_TRACER;
	return "NullObjectReferenceException";
}


/*************************************************************************/
}
}
}
}
