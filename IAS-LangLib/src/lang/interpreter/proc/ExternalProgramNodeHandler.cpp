/*
 * File: IAS-LangLib/src/lang/interpreter/proc/ExternalProgramNodeHandler.cpp
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
#include "ExternalProgramNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "CallbackRegister.h"
#include "ExecStore.h"

#include "exception/ProcessorLinkedException.h"


#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/stmt/Statement.h>

#include <lang/interpreter/extern/ModuleStore.h>
#include <lang/interpreter/extern/ModuleProxy.h>
#include <lang/interpreter/extern/Module.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {

/*************************************************************************/
ExternalProgramNodeHandler::ExternalProgramNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
ExternalProgramNodeHandler::~ExternalProgramNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExternalProgramNodeHandler::call(const Model::Node* pNode,
									  CallbackSignature::CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::ExternalProgramNode, pNode);
	const Model::ExternalProgramNode *pExternalProgramNode = IAS_DYNAMICCAST_CONST(Model::ExternalProgramNode, pNode);

	Extern::Module *pModule = pCtx->getExecStore()->getExternalModules()->getModule(pExternalProgramNode->getLibrary(),pExternalProgramNode->getModule());

	IAS_DFT_FACTORY<Exe::Stmt::Statement>::PtrHolder ptrStatement;
	IAS_DFT_FACTORY<Exe::Dec::Parameters>::PtrHolder ptrParameters;

	CallbackSignature::Result aSubResult;

	CallbackRegister::SubCall(pExternalProgramNode->getParametersNode(),pCtx,aSubResult);
	ptrParameters=aSubResult.pParameters;

	BlockChain::AutoPopUp autoPopUp(pCtx->getBlockChain(),ptrParameters);

	Exe::Program* pProgram = IAS_DFT_FACTORY<Exe::Program>::Create(ptrParameters.pass(),
												  	  	  	  	  	   pExternalProgramNode->isReturningResult());

	pCtx->getExecStore()->registerExecutable(pExternalProgramNode, pProgram);

  try{
	  pProgram->setStatement(pModule->createStatement(
                          pProgram->getParameters()->getType(),
                          pExternalProgramNode->getSymbol(),
													pExternalProgramNode->getParameters()));
	}catch(Exception& e){
			IAS_THROW(ProcessorLinkedException(e, pExternalProgramNode->getSourceLocation(), pExternalProgramNode));
	}

	pProgram->setSourceAndName(pExternalProgramNode->getQualifiedNameNode()->getQualifiedName(),
							   pCtx->getExecStore()->getModel()->resolve(pExternalProgramNode->getSourceLocation().getSourceID()));
}
/*************************************************************************/
}
}
}
}

