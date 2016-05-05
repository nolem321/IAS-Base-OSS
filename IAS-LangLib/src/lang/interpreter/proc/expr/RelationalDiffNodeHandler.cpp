/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/RelationalDiffNodeHandler.cpp
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
#include "RelationalDiffNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/RelationFamily.h>


namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
RelationalDiffNodeHandler::RelationalDiffNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
RelationalDiffNodeHandler::~RelationalDiffNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RelationalDiffNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::RelationalDiffNode, pNode);
	const Model::Expr::RelationalDiffNode *pDiffNode = IAS_DYNAMICCAST_CONST(Model::Expr::RelationalDiffNode, pNode);

	CallbackSignature::Result aResultLeft;
	CallbackRegister::SubCall(pDiffNode->getLeftExpr(),pCtx,aResultLeft);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExprLeft(aResultLeft.pExpr);

	CallbackSignature::Result aResultRight;
	CallbackRegister::SubCall(pDiffNode->getRightExpr(),pCtx,aResultRight);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExprRight(aResultRight.pExpr);

	aResult.pBooleanExpr=Exe::Expr::RelationFamily::Create(pCtx->getDataFactory(),
													  ptrExprLeft.pass(),
					 							      ptrExprRight.pass(),
													  &typeid(*pDiffNode));
}
/*************************************************************************/
}
}
}
}
}
