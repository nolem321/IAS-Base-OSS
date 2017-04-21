/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/CondValueNodeHandler.cpp
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
#include "CondValueNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/BooleanExpr.h>

#include <lang/interpreter/exe/expr/CondValue.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
CondValueNodeHandler::CondValueNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CondValueNodeHandler::~CondValueNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CondValueNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::CondValueNode, pNode);
	const  Model::Expr::CondValueNode *pCondValueNode = IAS_DYNAMICCAST_CONST(Model::Expr::CondValueNode, pNode);

	CallbackSignature::Result aResultTmp;

	CallbackRegister::SubCall(pCondValueNode->getExprNode(), pCtx, aResultTmp);
	IAS_DFT_FACTORY<Exe::Expr::BooleanExpr>::PtrHolder ptrCondition(aResultTmp.pBooleanExpr);

	CallbackRegister::SubCall(pCondValueNode->getExprTrueNode(), pCtx, aResultTmp);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExprTrue(aResultTmp.pExpr);

	CallbackRegister::SubCall(pCondValueNode->getExprFalseNode(), pCtx, aResultTmp);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrExprFalse(aResultTmp.pExpr);

	aResult.pExpr=
		IAS_DFT_FACTORY<Exe::Expr::CondValue>::Create(pCtx->getDataFactory(),
				ptrCondition.pass(),
				ptrExprTrue.pass(),
				ptrExprFalse.pass());

}
/*************************************************************************/
}
}
}
}
}
