/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/DetachNodeHandler.cpp
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
#include "DetachNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/Detach.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
DetachNodeHandler::DetachNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
DetachNodeHandler::~DetachNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DetachNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::DetachNode, pNode);
	const Model::Expr::DetachNode *pDetachNode = IAS_DYNAMICCAST_CONST(Model::Expr::DetachNode, pNode);

	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pDetachNode->getXPathAccessNode(),pCtx,aResultTmp);

	aResult.pExpr=IAS_DFT_FACTORY<Exe::Expr::Detach>::Create(aResultTmp.pXPathExprFamily);
}
/*************************************************************************/
}
}
}
}
}
