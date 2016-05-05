/*
 * File: IAS-LangLib/src/lang/interpreter/proc/dec/TypeDefinitionNodeHandler.cpp
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
#include "TypeDefinitionNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"
#include "../ExecStore.h"
#include <lang/interpreter/exe/allexe.h>


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Proc {
namespace Dec {

/*************************************************************************/
TypeDefinitionNodeHandler::TypeDefinitionNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
TypeDefinitionNodeHandler::~TypeDefinitionNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TypeDefinitionNodeHandler::call(const Model::Node* pNode,
									  CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::TypeDefinitionNode, pNode);
	const Model::Dec::TypeDefinitionNode *pTypeDefinitionNode = IAS_DYNAMICCAST_CONST(Model::Dec::TypeDefinitionNode, pNode);

	const DM::DataFactory *pDataFactory = pCtx->getDataFactory();

	IAS_DFT_FACTORY< Exe::Dec::TypeCreator >::PtrHolder ptrTypeCreator(IAS_DFT_FACTORY<Exe::Dec::TypeCreator>::Create());

	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
			pTypeDefinitionNode->getDeclarationsList().begin();

	const DM::Type *pBaseType=NULL;

	if(pTypeDefinitionNode->hasBaseType()){

		const Model::Dec::TypeInfoNode *pTypeInfoNode = pTypeDefinitionNode->getBaseType();

		pBaseType = pCtx->getExecStore()->resolveType(pTypeInfoNode->getType(),pTypeInfoNode->getNamespace());
	}

	while(itDeclarations != pTypeDefinitionNode->getDeclarationsList().end()){
		const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

		CallbackSignature::Result aSubCallResult;
		IAS_CHECK_IF_VALID(pDeclarationNode);
		CallbackRegister::SubCall(pDeclarationNode, pCtx, aSubCallResult);

		ptrTypeCreator->addProperty(aSubCallResult.pVariableDeclaration);

		itDeclarations++;
	}

	ptrTypeCreator->declareType(pCtx->getDataFactory(),
							    pTypeDefinitionNode->getName(),
							    pTypeDefinitionNode->getNamespace(),
							    pBaseType);


}
/*************************************************************************/
}
}
}
}
}
