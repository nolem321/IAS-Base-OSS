/*
 * File: IAS-LangLib/src/lang/printer/stmt/StatementsListNodeHandler.cpp
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
#include "StatementsListNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

namespace IAS {
namespace Lang {
namespace Printer {
namespace Stmt {

/*************************************************************************/
StatementsListNodeHandler::StatementsListNodeHandler() throw(){
	IAS_TRACER;
}

/*************************************************************************/
StatementsListNodeHandler::~StatementsListNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementsListNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::StatementsListNode, pNode);
	const Model::Stmt::StatementsListNode *pStatementsListNode = IAS_DYNAMICCAST_CONST(Model::Stmt::StatementsListNode, pNode);


	printIndent(pCtx,os);
	os<<"BEGIN\n";
	pCtx->iIndent++;
	int iNumDeclarations=pStatementsListNode->getDeclarationsList().size();
	if(iNumDeclarations)
		os<<"\n";
	{

		Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator it=
				pStatementsListNode->getDeclarationsList().begin();

		while(it != pStatementsListNode->getDeclarationsList().end()){
			const Model::Dec::DeclarationNode *pDeclarationNode = *it;
			CallbackRegister::SubCall(pDeclarationNode,pCtx,os);
			os<<";\n";
			it++;
		}


	}

	if(iNumDeclarations)
		os<<"\n";
	bool bFirst=true;
	bool bNewLine=false;
	{
		Model::Stmt::StatementsListNode::StatementNodesList::const_iterator it=
			pStatementsListNode->getStatementsList().begin();

		while(it != pStatementsListNode->getStatementsList().end()){

			const Model::Stmt::StatementNode *pStatementNode = *it;

			//Print a new line separator from time to time.
			if((!bFirst && (typeid(*pStatementNode) != typeid(Model::Stmt::AssignmentNode))) || bNewLine){
				os<<"\n";
				bNewLine=typeid(*pStatementNode) != typeid(Model::Stmt::AssignmentNode);
			}

			bFirst=false;

			CallbackRegister::SubCall(pStatementNode,pCtx,os);
			os<<";\n";
			it++;
		}


	}

	pCtx->iIndent--;
	printIndent(pCtx,os);
	os<<"END";

}
/*************************************************************************/
}
}
}
}
