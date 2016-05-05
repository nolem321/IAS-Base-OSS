/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/ForLoopNodeHandler.cpp
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
#include "ForLoopNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

#include <lang/interpreter/exe/allexe.h>
#include <lang/interpreter/exe/expr/RelationFamily.h>
#include <lang/interpreter/exe/expr/xpath/XPathExprFamily.h>
#include <lang/interpreter/exe/expr/BinaryExprFamily.h>
#include <lang/interpreter/exe/expr/xpath/BlockVariablesDataObjectExpr.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
ForLoopNodeHandler::ForLoopNodeHandler(){
	IAS_TRACER;
	ptrDftStepExpr=IAS_DFT_FACTORY<Model::Expr::ConstNode>::Create(Model::Expr::ConstNode::CN_INTEGER,"1");
}
/*************************************************************************/
ForLoopNodeHandler::~ForLoopNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ForLoopNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::ForLoopNode, pNode);
	const Model::Stmt::ForLoopNode *pForLoopNode = IAS_DYNAMICCAST_CONST(Model::Stmt::ForLoopNode, pNode);

	const Model::Expr::XPath::XPathAccessNode  *pXPathAccessNode = pForLoopNode->getXPathAccessNode();
	const Model::Expr::ExprNode         *pStartExprNode = pForLoopNode->getStartExprNode();
	const Model::Expr::ExprNode         *pStopExprNode = pForLoopNode->getStopExprNode();

	const Model::Stmt::StatementNode *pStatementNode = pForLoopNode->getStatementNode();

	CallbackSignature::Result aSubCallResult;
	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::XPath::XPathExprFamily>::PtrHolder ptrXPathExpr(aSubCallResult.pXPathExprFamily);


	/* Start Statement */
	CallbackRegister::SubCall(pStartExprNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrStartExpr(aSubCallResult.pExpr);

	IAS_DFT_FACTORY<Exe::Stmt::Assignment>::PtrHolder
	ptrStartStatement(IAS_DFT_FACTORY<Exe::Stmt::Assignment>::Create(
			IAS_DFT_FACTORY<Exe::Stmt::LeftSide>::Create(ptrXPathExpr.pass()),ptrStartExpr.pass())
		);


	/* Step  Statement */

	const Model::Expr::ExprNode *pStepExprNode=NULL;

	if(pForLoopNode->hasStepNode()){
		pStepExprNode = pForLoopNode->getStepExprNode();
		CallbackRegister::SubCall(pStepExprNode,pCtx,aSubCallResult);
	}else{
		CallbackRegister::SubCall(ptrDftStepExpr.getPointer(),pCtx,aSubCallResult);
	};

	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrRightExpr(aSubCallResult.pExpr);

	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aSubCallResult);
	ptrXPathExpr = aSubCallResult.pXPathExprFamily;

	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrEndExpr(
			Exe::Expr::BinaryExprFamily::Create(
						ptrXPathExpr.pass(),
						ptrRightExpr.pass(),
						&typeid(Model::Expr::AdditionNode))
	);

	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aSubCallResult);
	ptrXPathExpr = aSubCallResult.pXPathExprFamily;

	IAS_DFT_FACTORY<Exe::Stmt::Assignment>::PtrHolder
	ptrStepStatement(IAS_DFT_FACTORY<Exe::Stmt::Assignment>::Create(
			IAS_DFT_FACTORY<Exe::Stmt::LeftSide>::Create(ptrXPathExpr.pass()),
			ptrEndExpr.pass()));



	/* Condition */
	CallbackRegister::SubCall(pStopExprNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Expr::Expr>::PtrHolder ptrStopExpr(aSubCallResult.pExpr);


	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aSubCallResult);
	ptrXPathExpr = aSubCallResult.pXPathExprFamily;

	IAS_DFT_FACTORY<Exe::Expr::BooleanExpr>::PtrHolder ptrCondition;
	ptrCondition=Exe::Expr::RelationFamily::Create(pCtx->getDataFactory(),
													  ptrXPathExpr.pass(),
													  ptrStopExpr.pass(),
													  &typeid(Model::Expr::RelationalEqLessNode));

	/* Statements      */
	CallbackRegister::SubCall(pStatementNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Stmt::Statement>::PtrHolder ptrStatements(aSubCallResult.pStatement);


	aResult.pStatement=
			IAS_DFT_FACTORY<Exe::Stmt::ForLoop>::Create(ptrCondition.pass(),
													    ptrStatements.pass(),
													    ptrStartStatement.pass(),
													    ptrStepStatement.pass());

	aResult.pStatement->setSourceLine(pForLoopNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
