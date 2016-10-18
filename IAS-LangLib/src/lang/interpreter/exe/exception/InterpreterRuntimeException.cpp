/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/InterpreterRuntimeException.cpp
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
#include "InterpreterRuntimeException.h"

#include<lang/log/LogLevel.h>

namespace IAS{
namespace Lang {
namespace Interpreter{
namespace Exe{
/*************************************************************************/
InterpreterRuntimeException::InterpreterRuntimeException(org::invenireaude::lang::builtin::RuntimeException* dmRuntimeException, const String& strInfo):
	InterpreterProgramException(dmRuntimeException){
	IAS_TRACER;

	dmRuntimeException->setInfo(strInfo);

	setInfo(strInfo);
}
/*************************************************************************/
InterpreterRuntimeException::~InterpreterRuntimeException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void InterpreterRuntimeException::setStatementSource(const String& strSource, const String& strName){
	IAS_TRACER;

	InterpreterException::setStatementSource(strSource, strName);

	org::invenireaude::lang::builtin::RuntimeException* dmRuntimeException =
			org::invenireaude::lang::builtin::DataFactory::GetInstance()->getRuntimeExceptionType()->cast(dmValue);

	dmRuntimeException->setInfo(getInfo());

}
/*************************************************************************/
const char* InterpreterRuntimeException::getName(){
	IAS_TRACER;
	return "InterpreterRuntimeException";
}
/*************************************************************************/
}
}
}
}
