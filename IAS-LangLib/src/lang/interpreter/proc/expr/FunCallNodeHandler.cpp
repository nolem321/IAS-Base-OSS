/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/FunCallNodeHandler.cpp
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
#include "FunCallNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"
#include "../ExecStore.h"

#include "lang/interpreter/exe/expr/ExprList.h"
#include "lang/interpreter/exe/expr/FunCall.h"
#include "lang/interpreter/exe/Program.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {


/*************************************************************************/
FunCallNodeHandler::FunCallNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
FunCallNodeHandler::~FunCallNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void FunCallNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::FunCallNode, pNode);
	const Model::Expr::FunCallNode *pFunCallNode = IAS_DYNAMICCAST_CONST(Model::Expr::FunCallNode, pNode);

	const Model::Dec::QualifiedNameNode*  pQualifiedNameNode = pFunCallNode->getQualifiedNameNode();
	const Model::Expr::ExprListNode*      pExprListNode = pFunCallNode->getExprListNode();

	CallbackSignature::Result aResultExprList;
	CallbackRegister::SubCall(pExprListNode,pCtx,aResultExprList);


	TypeList lstSignatureTypes(aResultExprList.pExprList);

	Exe::Program *pProgram = pCtx->getExecStore()->createOrGetExecutable(pQualifiedNameNode->getQualifiedName(),
																 lstSignatureTypes);

	aResult.pExpr =  Exe::Expr::FunCall::Create(pProgram,aResultExprList.pExprList);

}
/*************************************************************************/
}
}
}
}
}
