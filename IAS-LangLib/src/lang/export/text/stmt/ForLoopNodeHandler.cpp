/*
 * File: IAS-LangLib/src/lang/export/text/stmt/ForLoopNodeHandler.cpp
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
namespace Export{
namespace Text {
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

	const Model::Expr::ExprNode      *pStartExprNode = pForLoopNode->getStartExprNode();
	const Model::Expr::ExprNode      *pStopExprNode = pForLoopNode->getStopExprNode();
	const Model::Stmt::StatementNode *pStatementNode = pForLoopNode->getStatementNode();

	printIndent(pCtx,aResult);
	printKeyword(aResult,"FOR");
	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aResult);
	aResult.ssOutput<<" = ";
	CallbackRegister::SubCall(pStartExprNode,pCtx,aResult);
  aResult.ssOutput<<" ";
	printKeyword(aResult,"TO");
  aResult.ssOutput<<" ";
	CallbackRegister::SubCall(pStopExprNode,pCtx,aResult);

	if(pForLoopNode->hasStepNode()){
    aResult.ssOutput<<" ";
		printKeyword(aResult,"STEP");
    aResult.ssOutput<<" ";
		CallbackRegister::SubCall(pForLoopNode->getStepExprNode(),pCtx,aResult);
	}
  aResult.ssOutput<<" ";
	printKeyword(aResult,"DO");
  aResult.ssOutput<<std::endl;
	pCtx->iIndent++;
	CallbackRegister::SubCall(pStatementNode,pCtx,aResult);
	pCtx->iIndent--;
}
/*************************************************************************/
}
}
}
}
}
