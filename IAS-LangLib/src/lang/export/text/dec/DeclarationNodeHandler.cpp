/*
 * File: IAS-LangLib/src/lang/export/text/dec/DeclarationNodeHandler.cpp
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
#include "../SourceStore.h"

namespace IAS {
namespace Lang {
namespace Export {
namespace Text {
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


	String strNamespace(pDeclarationNode->getNamespace());
	String strType(pDeclarationNode->getType());
	String strVariable(pDeclarationNode->getVariable());

	printKeyword(aResult,"VAR");
	aResult.ssOutput<<" "<<strVariable<<" ";
	printKeyword(aResult,"AS");
  aResult.ssOutput<<" ";
	printType(pCtx,aResult,strType, strNamespace);
}
/*************************************************************************/
}
}
}
}
}
