/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/StatementLists.cpp
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
#include "StatementLists.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/exception/InterpreterException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
StatementLists::StatementLists() throw(){
	IAS_TRACER;
	iSeq=0;
}
/*************************************************************************/
StatementLists::~StatementLists() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Deleted:"<<(void*)this<<","<<this->lstStatements.size());
}
/*************************************************************************/
void StatementLists::addStatement(Statement* pStatement){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pStatement);

	lstStatements.push_back(pStatement);
	phcStatements.addPointer(pStatement);
}
/*************************************************************************/
void StatementLists::execute(Context *pCtx) const{
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pCtx);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"BEGIN:"<<(void*)this);

	AutoPopUp autoPopUp(pCtx,createAndInitializeVariables());

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"size:"<<lstStatements.size());

	for(StatementList::const_iterator it = lstStatements.begin();
	    !pCtx->isInterrupted() && it != lstStatements.end();
	    it++){

		const Statement* pStatement = *it;


		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"line["<<pStatement->getSourceLine()
														<<"] "<<pStatement->getSource());

		try{
			pStatement->execute(pCtx);
		}catch(InterpreterException& e){
			e.setStatementLine(pStatement->getSourceLine());
			throw;
		}catch(Exception& e){
			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),e.getName()<<e.getInfo());
			InterpreterException newException;
			newException<<e.getName()<<" : "<<e.getInfo()<<" in [ "<<pStatement->getSource()<<" ]";
			newException.setStatementLine(pStatement->getSourceLine());
			IAS_THROW(newException);
		}
	}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"END:"<<(void*)this);
}
/*************************************************************************/
}
}
}
}
}
