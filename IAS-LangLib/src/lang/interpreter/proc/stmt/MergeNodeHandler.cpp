/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/MergeNodeHandler.cpp
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
#include "MergeNodeHandler.h"
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
MergeNodeHandler::MergeNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
MergeNodeHandler::~MergeNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MergeNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::MergeNode, pNode);
	const Model::Stmt::MergeNode *pMergeNode = IAS_DYNAMICCAST_CONST(Model::Stmt::MergeNode, pNode);

	const Model::Expr::ExprNode*     pExprNode = pMergeNode->getExpressionNode();
	const Model::Stmt::LeftSideNode* pLeftSideNode = pMergeNode->getLeftSideNode();
	
	CallbackSignature::Result aSubCallResult;
	CallbackRegister::SubCall(pLeftSideNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Stmt::LeftSide>::PtrHolder ptrLeftSide(aSubCallResult.pLeftSide);

	CallbackRegister::SubCall(pExprNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aSubCallResult.pExpr);

	IAS_DFT_FACTORY<Exe::Stmt::Merge>::PtrHolder
		ptrMerge(IAS_DFT_FACTORY<Exe::Stmt::Merge>::Create(ptrLeftSide.pass(),ptrExpr.pass()));

	ptrMerge->setSourceLine(pMergeNode->getSourceLocation().getLineNumber());

	aResult.pStatement=ptrMerge.pass();
}
/*************************************************************************/
}
}
}
}
}
