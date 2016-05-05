/*
 * File: IAS-LangLib/src/lang/export/text/stmt/IfThenElseNodeHandler.cpp
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
#include "IfThenElseNodeHandler.h"
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
IfThenElseNodeHandler::IfThenElseNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
IfThenElseNodeHandler::~IfThenElseNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IfThenElseNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::IfThenElseNode, pNode);
	const Model::Stmt::IfThenElseNode *pIfThenElseNode = IAS_DYNAMICCAST_CONST(Model::Stmt::IfThenElseNode, pNode);

	const Model::Expr::ExprNode      *pExprNode = pIfThenElseNode->getExprNode();
	const Model::Stmt::StatementNode *pThenStatementNode = pIfThenElseNode->getThenStatementNode();

	printKeyword(aResult,"IF ");
	CallbackRegister::SubCall(pExprNode,pCtx,aResult);
	printKeyword(aResult,"THEN\n");
	pCtx->iIndent++;
	printIndent(pCtx,aResult);
	CallbackRegister::SubCall(pThenStatementNode,pCtx,aResult);
	pCtx->iIndent--;

	if(pIfThenElseNode->hasElseStatementNode()){
		aResult.ssOutput<<"\n";
		printIndent(pCtx,aResult);
		printKeyword(aResult,"ELSE\n");
		pCtx->iIndent++;
		printIndent(pCtx,aResult);
		CallbackRegister::SubCall(pIfThenElseNode->getElseStatementNode(),pCtx,aResult);
		pCtx->iIndent--;
	}
}
/*************************************************************************/
}
}
}
}
}
