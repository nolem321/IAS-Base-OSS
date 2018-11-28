/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/StatementsListNodeHandler.cpp
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

#include <lang/interpreter/exe/allexe.h>

#include <lang/printer/CallbackRegister.h>


namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
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

	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
			pStatementsListNode->getDeclarationsList().begin();


	IAS_DFT_FACTORY<Exe::Stmt::StatementLists>::PtrHolder ptrExeStatementList(
			IAS_DFT_FACTORY<Exe::Stmt::StatementLists>::Create());

	while(itDeclarations != pStatementsListNode->getDeclarationsList().end()){

		IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Declaration ...");

		const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

		CallbackSignature::Result aSubCallResult;
		IAS_CHECK_IF_VALID(pDeclarationNode);
		CallbackRegister::SubCall(pDeclarationNode, pCtx, aSubCallResult);

		ptrExeStatementList->addVariable(aSubCallResult.pVariableDeclaration);

		itDeclarations++;
	}

	ptrExeStatementList->declareBlockVariables(pCtx->getDataFactory());

	BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(),ptrExeStatementList);

	Model::Stmt::StatementsListNode::StatementNodesList::const_iterator itStatements=
			pStatementsListNode->getStatementsList().begin();

	while(itStatements != pStatementsListNode->getStatementsList().end())
		try{

			const Model::Stmt::StatementNode *pStatementNode = *itStatements;
			IAS_CHECK_IF_VALID(pStatementNode);

			CallbackSignature::Result aSubCallResult;
			CallbackRegister::SubCall(pStatementNode, pCtx, aSubCallResult);

			ptrExeStatementList->addStatement(aSubCallResult.pStatement);

			//TODO (M) conditional ctx->bIncludeSource
			if(true){
				StringStream ssOutput;
				Printer::CallbackRegister::Call(pStatementNode,ssOutput);
				aSubCallResult.pStatement->setSource(ssOutput.str());
				IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"Added: "<<ssOutput.str());
			}

			itStatements++;

    }catch(ProcessorLinkedException& e){
			throw e;
		}catch(Exception& e){
			IAS_THROW(ProcessorLinkedException(e,(*itStatements)->getSourceLocation(),*itStatements));
		}

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isDetailedInfo(),"Setup:"<<(void*)ptrExeStatementList.getPointer());
	aResult.pStatement=ptrExeStatementList.pass();

	aResult.pStatement->setSourceLine(pStatementsListNode->getSourceLocation().getLineNumber());
}
/*************************************************************************/
}
}
}
}
}
