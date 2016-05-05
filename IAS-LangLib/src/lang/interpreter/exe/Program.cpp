/*
 * File: IAS-LangLib/src/lang/interpreter/exe/Program.cpp
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
#include "Program.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "stmt/Statement.h"
#include "dec/Parameters.h"
#include "Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {

/*************************************************************************/
Program::Program(Dec::Parameters *pParameters, bool bIsReturningResult):
		ptrParameters(pParameters),
		bIsReturningResult(bIsReturningResult){
	IAS_TRACER;

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"bIsReturningResult= "<<bIsReturningResult);
}
/*************************************************************************/
Program::~Program() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Deleted:"<<(void*)this<<","<<(void*)ptrMainStmtBlock);
}
/*************************************************************************/
void Program::execute(Context* pCtx){
	IAS_TRACER;

	if(ptrMainStmtBlock.isNull())
		IAS_THROW(InternalException(strName+strSourceName+"is empty()!"));

	ptrMainStmtBlock->execute(pCtx);
}
/*************************************************************************/
DM::DataObject *Program::createParameters(){
	IAS_TRACER;

	return ptrParameters->createAndInitializeVariables();
}
/*************************************************************************/
void Program::setStatement(Stmt::Statement* pMainStmtBlock){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pMainStmtBlock);
	this->ptrMainStmtBlock=pMainStmtBlock;
}
/*************************************************************************/
void Program::setSourceAndName(const String& strName, const String& strSourceName){
	IAS_TRACER;
	this->strName=strName;
	this->strSourceName=strSourceName;
}
/*************************************************************************/
}
}
}
}
