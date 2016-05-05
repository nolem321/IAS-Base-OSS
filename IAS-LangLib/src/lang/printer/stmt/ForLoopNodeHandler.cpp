/*
 * File: IAS-LangLib/src/lang/printer/stmt/ForLoopNodeHandler.cpp
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

namespace IAS {
namespace Lang {
namespace Printer {
namespace Stmt {

/*************************************************************************/
ForLoopNodeHandler::ForLoopNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ForLoopNodeHandler::~ForLoopNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ForLoopNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::ForLoopNode, pNode);
	const Model::Stmt::ForLoopNode *pForLoopNode = IAS_DYNAMICCAST_CONST(Model::Stmt::ForLoopNode, pNode);

	const Model::Expr::XPath::XPathAccessNode  *pXPathAccessNode = pForLoopNode->getXPathAccessNode();

	const Model::Expr::ExprNode      *pStartExprNode = pForLoopNode->getStartExprNode();
	const Model::Expr::ExprNode      *pStopExprNode = pForLoopNode->getStopExprNode();
	const Model::Stmt::StatementNode *pStatementNode = pForLoopNode->getStatementNode();

	printIndent(pCtx,os);
	os<<"FOR ";
	CallbackRegister::SubCall(pXPathAccessNode,pCtx,os);
	os<<" = ";
	CallbackRegister::SubCall(pStartExprNode,pCtx,os);
	os<<" TO ";
	CallbackRegister::SubCall(pStopExprNode,pCtx,os);

	if(pForLoopNode->hasStepNode()){
		os<<" STEP ";
		CallbackRegister::SubCall(pForLoopNode->getStepExprNode(),pCtx,os);
	}

	os<<" DO\n";
	pCtx->iIndent++;
	CallbackRegister::SubCall(pStatementNode,pCtx,os);
	pCtx->iIndent--;
}
/*************************************************************************/
}
}
}
}
