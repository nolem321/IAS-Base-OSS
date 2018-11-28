/*
 * File: IAS-LangLib/src/lang/export/text/dec/ParametersNodeHandler.cpp
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
#include "ParametersNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>

#include "../CallbackRegister.h"

namespace IAS {
namespace Lang {
namespace Export {
namespace Text {
namespace Dec {

/*************************************************************************/
ParametersNodeHandler::ParametersNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ParametersNodeHandler::~ParametersNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ParametersNodeHandler::call(const Model::Node* pNode,
									  CallbackCtx *pCtx,
									  CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Dec::ParametersNode, pNode);
	const Model::Dec::ParametersNode *pParametersNode = IAS_DYNAMICCAST_CONST(Model::Dec::ParametersNode, pNode);

	Model::Stmt::StatementsListNode::DeclarationNodesList::const_iterator itDeclarations=
			pParametersNode->getDeclarationsList().begin();

	aResult.ssOutput<<"(";

	bool bFirst = true;

	const Model::Dec::DeclarationNode * pDeclarationResultNode=NULL;

	while(itDeclarations != pParametersNode->getDeclarationsList().end()){
		const Model::Dec::DeclarationNode *pDeclarationNode = *itDeclarations;

		if((*itDeclarations)->getVariable().compare("result")){

			//if(!bFirst){
				aResult.ssOutput<<std::endl;
				printIndent(pCtx,aResult);
			//}

			CallbackSignature::Result aSubCallResult;
			IAS_CHECK_IF_VALID(pDeclarationNode);
			CallbackRegister::SubCall(pDeclarationNode, pCtx, aSubCallResult);

			aResult.ssOutput<<aSubCallResult.ssOutput.str();

			if(bFirst){
				aResult.ssOutput<<",";
				bFirst=false;
			}



		}else
			pDeclarationResultNode=pDeclarationNode;

		itDeclarations++;
	}

	aResult.ssOutput<<")"<<std::endl;

	if(pDeclarationResultNode){
		CallbackSignature::Result aSubCallResult;
		IAS_CHECK_IF_VALID(pDeclarationResultNode);
		CallbackRegister::SubCall(pDeclarationResultNode, pCtx, aSubCallResult);

		printKeyword(aResult,"RETURNS ");

		printType(pCtx,aResult,pDeclarationResultNode->getType(),pDeclarationResultNode->getNamespace());
	}

	aResult.ssOutput<<std::endl;
}
/*************************************************************************/
}
}
}
}
}
