/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Statement.cpp
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
#include "Statement.h"
#include<lang/log/LogLevel.h>
#include "lang/model/stmt/StatementNode.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Statement::Statement()throw():iLine(0){
	IAS_TRACER;
}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Deleted:"<<(void*)this<<","<<typeid(this).name());
}
/*************************************************************************/
void Statement::setSourceLine(unsigned short iLine){
	IAS_TRACER;
	this->iLine=iLine;
}
/*************************************************************************/
unsigned short Statement::getSourceLine()const{
	IAS_TRACER;

	return iLine;
}
/*************************************************************************/
}
}
}
}
}
