/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/PropertyNotSetException.cpp
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
#include "PropertyNotSetException.h"

#include<lang/log/LogLevel.h>

#include <org/invenireaude/lang/builtin/PropertyNotSetException.h>

using namespace org::invenireaude;

namespace IAS{
namespace Lang {
namespace Interpreter{
namespace Exe{
/*************************************************************************/
PropertyNotSetException::PropertyNotSetException(const String& strInfo):
		InterpreterRuntimeException(
				lang::builtin::DataFactory::GetInstance()->getPropertyNotSetExceptionType()->
				createPropertyNotSetException(), strInfo){

	IAS_TRACER;
}
/*************************************************************************/
PropertyNotSetException::~PropertyNotSetException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* PropertyNotSetException::getName(){
	IAS_TRACER;
	return "PropertyNotSetException";
}


/*************************************************************************/
}
}
}
}
