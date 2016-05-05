/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/TryCatchNodeHandler.cpp
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
#include "TryCatchNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"


#include <lang/interpreter/exe/stmt/TryCatch.h>
#include <lang/interpreter/exe/stmt/CatchList.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
TryCatchNodeHandler::TryCatchNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
TryCatchNodeHandler::~TryCatchNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TryCatchNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::TryCatchNode, pNode);
	const Model::Stmt::TryCatchNode *pTryCatchNode = IAS_DYNAMICCAST_CONST(Model::Stmt::TryCatchNode, pNode);

	const Model::Stmt::StatementNode*     pStatementNode = pTryCatchNode->getStatementNode();

	CallbackSignature::Result aSubStmtResult;
	CallbackRegister::SubCall(pStatementNode,pCtx,aSubStmtResult);
	IAS_DFT_FACTORY<Exe::Stmt::Statement>::PtrHolder ptrStatement(aSubStmtResult.pStatement);

	const Model::Stmt::CatchListNode*     pCatchListNode = pTryCatchNode->getCatchListNode();

	CallbackSignature::Result aSubCatchListResult;
	CallbackRegister::SubCall(pCatchListNode,pCtx,aSubCatchListResult);
	IAS_DFT_FACTORY<Exe::Stmt::CatchList>::PtrHolder ptrCatchList(aSubCatchListResult.pCatchList);


	aResult.pStatement =
			IAS_DFT_FACTORY<Exe::Stmt::TryCatch>::Create(ptrStatement.pass(),ptrCatchList.pass());

	aResult.pStatement->setSourceLine(pTryCatchNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
