/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/ThrowNodeHandler.cpp
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
#include "ThrowNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/stmt/Throw.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
ThrowNodeHandler::ThrowNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
ThrowNodeHandler::~ThrowNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ThrowNodeHandler::init(){
	IAS_TRACER;
}
/*************************************************************************/
void ThrowNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::ThrowNode, pNode);
	const Model::Stmt::ThrowNode *pThrowNode = IAS_DYNAMICCAST_CONST(Model::Stmt::ThrowNode, pNode);

	if(pThrowNode->hasExpression()){
		const Model::Expr::ExprNode*     pExprNode = pThrowNode->getExpressionNode();
		CallbackSignature::Result aSubCallResult;
		CallbackRegister::SubCall(pExprNode,pCtx,aSubCallResult);
		IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aSubCallResult.pExpr);

		aResult.pStatement=IAS_DFT_FACTORY<Exe::Stmt::Throw>::Create(ptrExpr.pass());
	}else
		aResult.pStatement=IAS_DFT_FACTORY<Exe::Stmt::Throw>::Create();

	aResult.pStatement->setSourceLine(pThrowNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
