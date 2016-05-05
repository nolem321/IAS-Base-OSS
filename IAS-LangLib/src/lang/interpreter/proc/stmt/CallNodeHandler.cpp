/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/CallNodeHandler.cpp
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
#include "CallNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"
#include "../ExecStore.h"

#include "lang/interpreter/exe/expr/ExprList.h"
#include "lang/interpreter/exe/stmt/Call.h"
#include "lang/interpreter/exe/Program.h"

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {


/*************************************************************************/
CallNodeHandler::CallNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
CallNodeHandler::~CallNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CallNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::CallNode, pNode);
	const Model::Stmt::CallNode *pCallNode = IAS_DYNAMICCAST_CONST(Model::Stmt::CallNode, pNode);

	const Model::Dec::QualifiedNameNode*  pQualifiedNameNode = pCallNode->getQualifiedNameNode();
	const Model::Expr::ExprListNode*      pExprListNode = pCallNode->getExprListNode();

	CallbackSignature::Result aResultExprList;
	CallbackRegister::SubCall(pExprListNode,pCtx,aResultExprList);

	TypeList lstSignatureTypes(aResultExprList.pExprList);

	Exe::Program *pProgram = pCtx->getExecStore()->getExecutable(pQualifiedNameNode->getQualifiedName(),
																lstSignatureTypes);

	aResult.pStatement = IAS_DFT_FACTORY<Exe::Stmt::Call>::Create(pProgram,aResultExprList.pExprList);

	aResult.pStatement->setSourceLine(pCallNode->getSourceLocation().getLineNumber());

}
/*************************************************************************/
}
}
}
}
}
