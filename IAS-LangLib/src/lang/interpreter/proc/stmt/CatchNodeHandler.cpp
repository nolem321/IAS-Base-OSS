/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/CatchNodeHandler.cpp
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
#include "CatchNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/stmt/Catch.h>
#include <lang/interpreter/exe/stmt/Statement.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
CatchNodeHandler::CatchNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CatchNodeHandler::~CatchNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CatchNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::CatchNode, pNode);
	const Model::Stmt::CatchNode *pCatchNode = IAS_DYNAMICCAST_CONST(Model::Stmt::CatchNode, pNode);

	IAS_DFT_FACTORY<Exe::Stmt::Catch>::PtrHolder ptrCatchStatement(
			IAS_DFT_FACTORY<Exe::Stmt::Catch>::Create());

	const Model::Dec::DeclarationNode*     pDeclarationNode = pCatchNode->getDeclarationNode();

	CallbackSignature::Result aSubDeclarationResult;
	CallbackRegister::SubCall(pDeclarationNode,pCtx,aSubDeclarationResult);
	ptrCatchStatement->setCatchVariable(aSubDeclarationResult.pVariableDeclaration);

	ptrCatchStatement->declareBlockVariables(pCtx->getDataFactory());

	BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(),ptrCatchStatement);

	const Model::Stmt::StatementNode*     pStatementNode = pCatchNode->getStatementNode();

	CallbackSignature::Result aSubStmtResult;
	CallbackRegister::SubCall(pStatementNode,pCtx,aSubStmtResult);

	ptrCatchStatement->setCatchStatement(aSubStmtResult.pStatement);

	aResult.pCatch = ptrCatchStatement.pass();
}
/*************************************************************************/
}
}
}
}
}
