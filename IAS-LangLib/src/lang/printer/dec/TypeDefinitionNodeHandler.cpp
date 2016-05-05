/*
 * File: IAS-LangLib/src/lang/printer/dec/TypeDefinitionNodeHandler.cpp
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

namespace IAS {
namespace Lang {
namespace Printer {
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
void TypeDefinitionNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os){

	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::TypeDefinitionNode, pNode);
	const Model::Dec::TypeDefinitionNode *pTypeDefinitionNode = IAS_DYNAMICCAST_CONST(Model::Dec::TypeDefinitionNode, pNode);

	os<<"\nDEFINE "<<pTypeDefinitionNode->getName();
	os<<" : \""<<pTypeDefinitionNode->getNamespace()<<"\" AS ";

	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
				pTypeDefinitionNode->getDeclarationsList().begin();

	const DM::Type *pBaseType=NULL;

	if(pTypeDefinitionNode->hasBaseType()){

		os<<"\n EXTENSION OF ";
		const Model::Dec::TypeInfoNode *pTypeInfoNode = pTypeDefinitionNode->getBaseType();
		os<<pTypeInfoNode->getType();
		os<<" : \""<<pTypeInfoNode->getNamespace()<<"\"\n";
	}

	if(itDeclarations != pTypeDefinitionNode->getDeclarationsList().end()){
		os <<"BEGIN\n";

		bool bFirst=true;
		while(itDeclarations != pTypeDefinitionNode->getDeclarationsList().end()){
			const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

			if(!bFirst)
				os<<"\n";

			bFirst=false;
			IAS_CHECK_IF_VALID(pDeclarationNode);

			os<<"   "<<pDeclarationNode->getVariable()<<" AS ";
			os<<pDeclarationNode->getType();

			if(pDeclarationNode->hasNamespace() &&
				pDeclarationNode->getNamespace().compare(DM::DataFactory::BuildInTypesNamespace) != 0){
				os<<" : \""<<pDeclarationNode->getNamespace()<<"\" ";
			}


			os<<";";
			itDeclarations++;
			}

		os <<"\nEND;\n";
	}

}
/*************************************************************************/
}
}
}
}
