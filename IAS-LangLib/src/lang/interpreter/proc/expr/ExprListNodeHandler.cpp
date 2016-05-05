/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/ExprListNodeHandler.cpp
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
#include "ExprListNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/ExprList.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Expr {

/*************************************************************************/
ExprListNodeHandler::ExprListNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ExprListNodeHandler::~ExprListNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExprListNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ExprListNode, pNode);
	const Model::Expr::ExprListNode *pExprListNode = IAS_DYNAMICCAST_CONST(Model::Expr::ExprListNode, pNode);

	const Model::Expr::ExprListNode::ExprNodeList& lstExprNodes = pExprListNode->getExprNodes();

	IAS_DFT_FACTORY<Exe::Expr::ExprList>::PtrHolder ptrExprList(
			IAS_DFT_FACTORY<Exe::Expr::ExprList>::Create(lstExprNodes.size()));

	for(Model::Expr::ExprListNode::ExprNodeList::const_iterator it = lstExprNodes.begin();
		it != lstExprNodes.end();
		it++){

		CallbackSignature::Result aResultExpr;
		CallbackRegister::SubCall((*it),pCtx,aResultExpr);
		ptrExprList->addExpr(aResultExpr.pExpr);
	}

	aResult.pExprList = ptrExprList.pass();
}
/*************************************************************************/
}
}
}
}
}
