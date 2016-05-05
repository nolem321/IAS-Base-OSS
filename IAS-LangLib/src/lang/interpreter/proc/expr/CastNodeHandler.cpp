/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/CastNodeHandler.cpp
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
#include "CastNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/CastExprFamily.h>

#include "../ExecStore.h"


namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
CastNodeHandler::CastNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CastNodeHandler::~CastNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CastNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::CastNode, pNode);
	const Model::Expr::CastNode *pCastNode = IAS_DYNAMICCAST_CONST(Model::Expr::CastNode, pNode);

	CallbackSignature::Result aResultExpr;
	CallbackRegister::SubCall(pCastNode->getChild(), pCtx, aResultExpr);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExpr(aResultExpr.pExpr);

	const Model::Dec::TypeInfoNode *pTypeInfoNode = pCastNode->getTypeInfoNode();

	String strNamespace(pTypeInfoNode->getNamespace());
	String strName(pTypeInfoNode->getType());

	const DM::Type* pType = pCtx->getExecStore()->resolveType(strName,strNamespace);


	aResult.pExpr=Exe::Expr::CastExprFamily::Create(ptrExpr.pass(),pType);

}
/*************************************************************************/
}
}
}
}
}
