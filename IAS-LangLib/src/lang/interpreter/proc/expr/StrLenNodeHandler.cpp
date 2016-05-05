/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/StrLenNodeHandler.cpp
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
#include "StrLenNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/StrLenExpr.h>


namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
StrLenNodeHandler::StrLenNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
StrLenNodeHandler::~StrLenNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StrLenNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::StrLenNode, pNode);
	const Model::Expr::StrLenNode *pStrLenNode = IAS_DYNAMICCAST_CONST(Model::Expr::StrLenNode, pNode);


	CallbackSignature::Result aResultExpr;
	CallbackRegister::SubCall(pStrLenNode->getChild(),pCtx,aResultExpr);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aResultExpr.pExpr);

	aResult.pExpr=IAS_DFT_FACTORY<Exe::Expr::StrLenExpr>::Create(pCtx->getDataFactory(),ptrExpr.pass());

}
/*************************************************************************/
}
}
}
}
}
