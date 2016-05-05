/*
 * File: IAS-LangLib/src/lang/printer/stmt/IfThenElseNodeHandler.cpp
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
namespace Printer {
namespace Stmt {

/*************************************************************************/
IfThenElseNodeHandler::IfThenElseNodeHandler() throw(){
	IAS_TRACER;
}

/*************************************************************************/
IfThenElseNodeHandler::~IfThenElseNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IfThenElseNodeHandler::call(const Model::Node* pNode,
						    CallbackCtx *pCtx,
						    std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::IfThenElseNode, pNode);
	const Model::Stmt::IfThenElseNode *pIfThenElseNode = IAS_DYNAMICCAST_CONST(Model::Stmt::IfThenElseNode, pNode);

	const Model::Expr::ExprNode      *pExprNode = pIfThenElseNode->getExprNode();
	const Model::Stmt::StatementNode *pThenStatementNode = pIfThenElseNode->getThenStatementNode();

	printIndent(pCtx,os);
	os<<"IF ";
	CallbackRegister::SubCall(pExprNode,pCtx,os);
	os<<" THEN\n";
	pCtx->iIndent++;
	CallbackRegister::SubCall(pThenStatementNode,pCtx,os);
	pCtx->iIndent--;

	if(pIfThenElseNode->hasElseStatementNode()){
		os<<"\n";
		printIndent(pCtx,os);
		os<<"ELSE\n";
		pCtx->iIndent++;
		CallbackRegister::SubCall(pIfThenElseNode->getElseStatementNode(),pCtx,os);
		pCtx->iIndent--;
	}
}
/*************************************************************************/
}
}
}
}
