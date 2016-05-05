/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/GetTypeNSNodeHandler.cpp
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
#include "GetTypeNSNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"
#include <lang/interpreter/exe/expr/GetTypeNSExpr.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
GetTypeNSNodeHandler::GetTypeNSNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
GetTypeNSNodeHandler::~GetTypeNSNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetTypeNSNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::GetTypeNSNode, pNode);
	const Model::Expr::GetTypeNSNode *pGetTypeNSNode = IAS_DYNAMICCAST_CONST(Model::Expr::GetTypeNSNode, pNode);

	CallbackSignature::Result aResultExpr;
	CallbackRegister::SubCall(pGetTypeNSNode->getChild(),pCtx,aResultExpr);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aResultExpr.pExpr);

	aResult.pExpr=IAS_DFT_FACTORY<Exe::Expr::GetTypeNSExpr>::Create(pCtx->getDataFactory(),ptrExpr.pass());
}
/*************************************************************************/
}
}
}
}
}
