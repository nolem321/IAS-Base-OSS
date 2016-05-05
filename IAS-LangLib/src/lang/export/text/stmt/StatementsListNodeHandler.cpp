/*
 * File: IAS-LangLib/src/lang/export/text/stmt/StatementsListNodeHandler.cpp
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
#include "../exception/ProcessorLinkedException.h"

#include <lang/printer/CallbackRegister.h>


namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Stmt {

/*************************************************************************/
StatementsListNodeHandler::StatementsListNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
StatementsListNodeHandler::~StatementsListNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementsListNodeHandler::call(const Model::Node* pNode,
										 CallbackCtx *pCtx,
										 CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::StatementsListNode, pNode);
	const Model::Stmt::StatementsListNode *pStatementsListNode = IAS_DYNAMICCAST_CONST(Model::Stmt::StatementsListNode, pNode);


	printKeyword(aResult,"BEGIN");
	aResult.ssOutput<<"\n";
	pCtx->iIndent++;
	int iNumDeclarations=pStatementsListNode->getDeclarationsList().size();
	{

		Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator it=
				pStatementsListNode->getDeclarationsList().begin();

		while(it != pStatementsListNode->getDeclarationsList().end()){
			const Model::Dec::DeclarationNode *pDeclarationNode = *it;

			printIndent(pCtx,aResult);
			CallbackRegister::SubCall(pDeclarationNode,pCtx,aResult);
			aResult.ssOutput<<";\n";
			it++;
		}


	}

	if(iNumDeclarations){
		aResult.ssOutput<<"\n";
	}

	{
		Model::Stmt::StatementsListNode::StatementNodesList::const_iterator it=
			pStatementsListNode->getStatementsList().begin();

		while(it != pStatementsListNode->getStatementsList().end()){

			const Model::Stmt::StatementNode *pStatementNode = *it;


			printIndent(pCtx,aResult);
			CallbackRegister::SubCall(pStatementNode,pCtx,aResult);
			aResult.ssOutput<<";\n";
			it++;
		}


	}

	pCtx->iIndent--;
	printIndent(pCtx,aResult);
	printKeyword(aResult,"END");

}
/*************************************************************************/
}
}
}
}
}
