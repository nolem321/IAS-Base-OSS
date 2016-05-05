/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/DeclarationNodeHandler.cpp
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
#include "DeclarationNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"
#include "../ExecStore.h"
#include <lang/interpreter/exe/dec/VariableDeclaration.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
DeclarationNodeHandler::DeclarationNodeHandler(){}
/*************************************************************************/
DeclarationNodeHandler::~DeclarationNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DeclarationNodeHandler::call(const Model::Node* pNode,
									  CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::DeclarationNode, pNode);
	const Model::Dec::DeclarationNode *pDeclarationNode = IAS_DYNAMICCAST_CONST(Model::Dec::DeclarationNode, pNode);

	handle(pDeclarationNode,pCtx,aResult);
}

/*************************************************************************/
void DeclarationNodeHandler::handle(const Model::Dec::DeclarationNode* pDeclarationNode,
								    CallbackCtx *pCtx,
									CallbackSignature::Result& aResult){
	IAS_TRACER;

	const DM::DataFactory *pDataFactory = pCtx->getDataFactory();

	String strNamespace(pDeclarationNode->getNamespace());
	String strName(pDeclarationNode->getType());
	const DM::Type *pType = pCtx->getExecStore()->resolveType(strName,strNamespace);

	IAS_DFT_FACTORY<Exe::Dec::VariableDeclaration>::PtrHolder ptrVariableDeclaration;

	ptrVariableDeclaration=IAS_DFT_FACTORY<Exe::Dec::VariableDeclaration>::Create(pDeclarationNode->getVariable(),
																	 	 	 	 pType,
																	 	 	 	 pDeclarationNode->isArray());

	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"DeclarationNodeHandler: "<<pDeclarationNode->getVariable()<<", "<<(void*)ptrVariableDeclaration);

	aResult.pVariableDeclaration=ptrVariableDeclaration.pass();
}
/*************************************************************************/
}
}
}
}
}
