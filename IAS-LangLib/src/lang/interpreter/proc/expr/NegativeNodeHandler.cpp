/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/NegativeNodeHandler.cpp
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
#include "NegativeNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/UnaryExprFamily.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
NegativeNodeHandler::NegativeNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
NegativeNodeHandler::~NegativeNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void NegativeNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::NegativeNode, pNode);
	const Model::Expr::NegativeNode *pNegativeNode = IAS_DYNAMICCAST_CONST(Model::Expr::NegativeNode, pNode);

	CallbackSignature::Result aResultExpr;
	CallbackRegister::SubCall(pNegativeNode->getChild(),pCtx,aResultExpr);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aResultExpr.pExpr);

	aResult.pExpr=Exe::Expr::UnaryExprFamily::Create(ptrExpr.pass(),
													&typeid(Model::Expr::NegativeNode));
}
/*************************************************************************/
}
}
}
}
}
