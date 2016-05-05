/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/WhileLoopNodeHandler.cpp
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
#include "WhileLoopNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

#include <lang/interpreter/exe/allexe.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
WhileLoopNodeHandler::WhileLoopNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
WhileLoopNodeHandler::~WhileLoopNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WhileLoopNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::WhileLoopNode, pNode);
	const Model::Stmt::WhileLoopNode *pWhileLoopNode = IAS_DYNAMICCAST_CONST(Model::Stmt::WhileLoopNode, pNode);

	const Model::Expr::LogicalExprNode *pExprNode = pWhileLoopNode->getLogicalExprNode();
	const Model::Stmt::StatementNode   *pStatementNode = pWhileLoopNode->getStatementNode();

	CallbackSignature::Result aSubCallResult;
	CallbackRegister::SubCall(pExprNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::BooleanExpr>::PtrHolder ptrCondition(aSubCallResult.pBooleanExpr);

	CallbackRegister::SubCall(pStatementNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Stmt::Statement>::PtrHolder ptrStatements(aSubCallResult.pStatement);

	aResult.pStatement=
			IAS_DFT_FACTORY<Exe::Stmt::WhileLoop>::Create(ptrCondition.pass(),
													 ptrStatements.pass());


	aResult.pStatement->setSourceLine(pWhileLoopNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
