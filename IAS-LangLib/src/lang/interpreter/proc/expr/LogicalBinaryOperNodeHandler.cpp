/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/LogicalBinaryOperNodeHandler.cpp
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
#include "LogicalBinaryOperNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>


#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/LogicalBinaryOperFamily.h>


namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
LogicalBinaryOperNodeHandler::LogicalBinaryOperNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
LogicalBinaryOperNodeHandler::~LogicalBinaryOperNodeHandler() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void LogicalBinaryOperNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::LogicalBinaryOperNode, pNode);
	const Model::Expr::LogicalBinaryOperNode *pLogicalBinaryOperNode = IAS_DYNAMICCAST_CONST(Model::Expr::LogicalBinaryOperNode, pNode);

	CallbackSignature::Result aResultLeft;
	CallbackRegister::SubCall(pLogicalBinaryOperNode->getLeftExpr(),pCtx,aResultLeft);
	IAS_DFT_FACTORY<Exe::Expr::BooleanExpr>::PtrHolder ptrExprLeft(aResultLeft.pBooleanExpr);

	CallbackSignature::Result aResultRight;
	CallbackRegister::SubCall(pLogicalBinaryOperNode->getRightExpr(),pCtx,aResultRight);
	IAS_DFT_FACTORY<Exe::Expr::BooleanExpr>::PtrHolder ptrExprRight(aResultRight.pBooleanExpr);

	aResult.pBooleanExpr=Exe::Expr::LogicalBinaryOperFamily::Create(pCtx->getDataFactory(),
															  ptrExprLeft.pass(),
															  ptrExprRight.pass(),
															  &typeid(*pLogicalBinaryOperNode));

}
/*************************************************************************/
}
}
}
}
}
