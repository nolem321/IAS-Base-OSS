/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/WithNodeHandler.cpp
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
#include "WithNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

#include <lang/interpreter/exe/allexe.h>
#include <lang/interpreter/exe/expr/xpath/XPathExprFamily.h>
#include <lang/interpreter/exe/expr/xpath/BlockVariablesDataObjectExpr.h>
namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
WithNodeHandler::WithNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
WithNodeHandler::~WithNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WithNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::WithNode, pNode);
	const Model::Stmt::WithNode *pWithNode = IAS_DYNAMICCAST_CONST(Model::Stmt::WithNode, pNode);

	const Model::Expr::XPath::XPathAccessNode   *pXPathAccessNode = pWithNode->getVariableExpr();
	const Model::Stmt::StatementNode     *pStatementNode   = pWithNode->getStatementNode();

	IAS_DFT_FACTORY<Exe::Stmt::With>::PtrHolder ptrWithStatement;

	IAS_DFT_FACTORY<Exe::Expr::XPath::XPathExprFamily>::PtrHolder ptrExpr(createVarExpr(pCtx,pXPathAccessNode));


	if(pWithNode->hasVariable()){
		if(ptrExpr->isArray()){
			ptrWithStatement=IAS_DFT_FACTORY<Exe::Stmt::WithArray>::Create(pWithNode->getVariable(),ptrExpr.pass());
		}else{
			ptrWithStatement=IAS_DFT_FACTORY<Exe::Stmt::WithNonArray>::Create(pWithNode->getVariable(),ptrExpr.pass());
		}
	}else{
		if(ptrExpr->isArray()){
			ptrWithStatement=IAS_DFT_FACTORY<Exe::Stmt::WithArray>::Create(ptrExpr.pass());
		}else{
			ptrWithStatement=IAS_DFT_FACTORY<Exe::Stmt::WithNonArray>::Create(ptrExpr.pass());
		}
	}

	BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(),ptrWithStatement);
	CallbackSignature::Result aSubCallResult;

	ptrWithStatement->declareBlockVariables(pCtx->getDataFactory());

	/* Statements      */
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"WITH statements :  ");

	CallbackRegister::SubCall(pStatementNode,pCtx,aSubCallResult);

	ptrWithStatement->setStatement(aSubCallResult.pStatement);

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"End of WITH");
	aResult.pStatement=ptrWithStatement.pass();

	aResult.pStatement->setSourceLine(pWithNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
Exe::Expr::XPath::XPathExprFamily* WithNodeHandler::createVarExpr(CallbackCtx *pCtx,
		const Model::Expr::XPath::XPathAccessNode *pXPathAccessNode) {


	CallbackSignature::Result aResultTmp;
	CallbackRegister::SubCall(pXPathAccessNode, pCtx, aResultTmp);
	return aResultTmp.pXPathExprFamily;
}
/*************************************************************************/
}
}
}
}
}
