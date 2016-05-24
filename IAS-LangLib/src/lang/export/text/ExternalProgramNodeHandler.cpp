/*
 * File: IAS-LangLib/src/lang/export/text/ExternalProgramNodeHandler.cpp
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
#include "SourceStore.h"

#include <lang/interpreter/exe/dec/Parameters.h>
#include <lang/interpreter/exe/Program.h>
#include <lang/interpreter/exe/stmt/Statement.h>

#include <lang/interpreter/extern/ModuleStore.h>
#include <lang/interpreter/extern/ModuleProxy.h>
#include <lang/interpreter/extern/Module.h>

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {

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

	printIndent(pCtx,aResult);

	printKeyword(aResult,"PROGRAM");
	CallbackRegister::SubCall(pExternalProgramNode->getQualifiedNameNode(),pCtx,aResult);
	pCtx->iIndent+=5;
	CallbackRegister::SubCall(pExternalProgramNode->getParametersNode(),pCtx,aResult);
	pCtx->iIndent-=5;

	if(pCtx->bDeclarationOnly)
		return;

	printIndent(pCtx,aResult);
	printKeyword(aResult,"EXTERNAL");
	aResult.ssOutput<<pExternalProgramNode->getLibrary();
	aResult.ssOutput<<":"<<pExternalProgramNode->getModule();
	aResult.ssOutput<<":"<<pExternalProgramNode->getSymbol();
	aResult.ssOutput<<"\"(";

	const StringList& lstParameters(pExternalProgramNode->getParameters());

	for(StringList::const_iterator it=lstParameters.begin(); it != lstParameters.end(); it++){
		if(it !=lstParameters.begin())
			aResult.ssOutput<<",";
		aResult.ssOutput<<"\n\""<<(*it)<<'"';
	}
	aResult.ssOutput<<");"<<std::endl;

}
/*************************************************************************/
}
}
}
}

