/*
 * File: IAS-LangLib/src/lang/interpreter/proc/StandardProgramNodeHandler.cpp
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
#include "StandardProgramNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "CallbackRegister.h"
#include "ExecStore.h"

#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/stmt/Statement.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
StandardProgramNodeHandler::StandardProgramNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
StandardProgramNodeHandler::~StandardProgramNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StandardProgramNodeHandler::call(const Model::Node* pNode,
								 CallbackCtx *pCtx,
								 CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::StandardProgramNode, pNode);
	const Model::StandardProgramNode *pStandardProgramNode = IAS_DYNAMICCAST_CONST(Model::StandardProgramNode, pNode);

	IAS_DFT_FACTORY<Exe::Stmt::Statement>::PtrHolder ptrStatement;
	IAS_DFT_FACTORY<Exe::Dec::Parameters>::PtrHolder ptrParameters;

	CallbackSignature::Result aSubResult;

	CallbackRegister::SubCall(pStandardProgramNode->getParametersNode(),pCtx,aSubResult);
	ptrParameters=aSubResult.pParameters;

	BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(),ptrParameters);

	Exe::Program* pProgram = IAS_DFT_FACTORY<Exe::Program>::Create(ptrParameters.pass(),
			                                      pStandardProgramNode->isReturningResult());

	pCtx->getExecStore()->registerExecutable(pStandardProgramNode, pProgram);

	CallbackRegister::SubCall(pStandardProgramNode->getStatementListNode(),pCtx,aSubResult);
	pProgram->setStatement(aSubResult.pStatement);

	pProgram->setSourceAndName(pStandardProgramNode->getQualifiedNameNode()->getQualifiedName(),
						pCtx->getExecStore()->getModel()->resolve(pStandardProgramNode->getSourceLocation().getSourceID()));
}
/*************************************************************************/
}
}
}
}

