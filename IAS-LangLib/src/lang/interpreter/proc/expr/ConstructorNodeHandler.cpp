/*
 * File: IAS-LangLib/src/lang/interpreter/proc/expr/ConstructorNodeHandler.cpp
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
#include "ConstructorNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"
#include "../ExecStore.h"

#include <lang/interpreter/exe/expr/Expr.h>
#include <lang/interpreter/exe/expr/ConstructorExpr.h>
#include <lang/interpreter/exe/expr/ConstructorWithStatementExpr.h>
#include <lang/interpreter/exe/stmt/Statement.h>
namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Expr {

/*************************************************************************/
ConstructorNodeHandler::ConstructorNodeHandler(){}
/*************************************************************************/
ConstructorNodeHandler::~ConstructorNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ConstructorNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ConstructorNode, pNode);
	const Model::Expr::ConstructorNode *pConstructorNode = IAS_DYNAMICCAST_CONST(Model::Expr::ConstructorNode, pNode);

	String strNamespace(pConstructorNode->getTypeURI());
	String strName(pConstructorNode->getTypeName());
	const DM::Type *pType = pCtx->getExecStore()->resolveType(strName,strNamespace);

	if(!pConstructorNode->hasStatement()){
		aResult.pExpr=IAS_DFT_FACTORY<Exe::Expr::ConstructorExpr>::Create(pType);
	}else{
		const Model::Stmt::StatementNode *pStatementNode = pConstructorNode->getStatementNode();

		IAS_DFT_FACTORY<Exe::Expr::ConstructorWithStatementExpr>::PtrHolder ptrConstructor(
				IAS_DFT_FACTORY<Exe::Expr::ConstructorWithStatementExpr>::Create(pType));

		BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(), ptrConstructor);
		CallbackSignature::Result aSubCallResult;

		/* Statements      */
		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Constructor statements :  ");

		CallbackRegister::SubCall(pStatementNode,pCtx,aSubCallResult);

		ptrConstructor->setStatement(aSubCallResult.pStatement);

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"End of WITH");

		aResult.pExpr=ptrConstructor.pass();

	}
}
/*************************************************************************/
}
}
}
}
}
