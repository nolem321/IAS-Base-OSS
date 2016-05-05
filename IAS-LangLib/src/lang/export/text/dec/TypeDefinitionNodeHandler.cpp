/*
 * File: IAS-LangLib/src/lang/export/text/dec/TypeDefinitionNodeHandler.cpp
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
#include "../SourceStore.h"

namespace IAS {
namespace Lang {
namespace Export {
namespace Text {
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


	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
			pTypeDefinitionNode->getDeclarationsList().begin();

	const DM::Type *pBaseType=NULL;

	aResult.ssOutput<<"DEFINE"<<std::endl;

	if(pTypeDefinitionNode->hasBaseType()){

		const Model::Dec::TypeInfoNode *pTypeInfoNode = pTypeDefinitionNode->getBaseType();
		//pBaseType = pCtx->getDataFactory()->getType(pTypeInfoNode->getNamespace(),pTypeInfoNode->getType());
	}

	aResult.ssOutput<<"BEGIN"<<std::endl;

	bool bFirst = true;

	while(itDeclarations != pTypeDefinitionNode->getDeclarationsList().end()){
		const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

		CallbackSignature::Result aSubCallResult;
		IAS_CHECK_IF_VALID(pDeclarationNode);
		CallbackRegister::SubCall(pDeclarationNode, pCtx, aSubCallResult);

		if(!bFirst) {
			aResult.ssOutput<<";";
			bFirst=false;
		}

		aResult.ssOutput<<aSubCallResult.ssOutput<<std::endl;
	}

	aResult.ssOutput<<"END"<<std::endl;

}
/*************************************************************************/
}
}
}
}
}
