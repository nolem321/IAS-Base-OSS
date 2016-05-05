/*
 * File: IAS-LangLib/src/lang/interpreter/exe/exception/InterpreterException.cpp
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
#include "InterpreterException.h"

#include<lang/log/LogLevel.h>

#include <lang/interpreter/exe/stmt/Statement.h>
#include <lang/model/stmt/StatementNode.h>
#include <lang/tools/parser/SourceLocation.h>


namespace IAS{
namespace Lang {
namespace Interpreter{
namespace Exe{
/*************************************************************************/
InterpreterException::InterpreterException():iLine(0),iStack(0){
	IAS_TRACER;
}

/*************************************************************************/
InterpreterException::InterpreterException(const String& strInfo):iLine(0),iStack(0){

	IAS_TRACER;
	setInfo(strInfo);
}
/*************************************************************************/
InterpreterException::~InterpreterException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* InterpreterException::getName(){
	IAS_TRACER;
	return "InterpreterException";
}
/*************************************************************************/
void InterpreterException::setStatementSource(const String& strSource, const String& strName){
	IAS_TRACER;

	String strTmp;

	static const int CMaxFileLen = 45;

	if(strSource.length() > CMaxFileLen)
		strTmp = "<.." + strSource.substr(strSource.length() - CMaxFileLen, CMaxFileLen);
	else
		strTmp = strSource;

	(*this)<<"\n "<<"["<<++iStack<<"] "<<strTmp<<"("<<iLine<<"), "<<strName<<"\t";
	iLine=0;
}
/*************************************************************************/
}
}
}
}
