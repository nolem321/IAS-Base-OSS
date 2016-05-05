/*
 * File: IAS-LangLib/src/lang/printer/ExternalProgramNodeHandler.cpp
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

namespace IAS {
namespace Lang {
namespace Printer {

/*************************************************************************/
ExternalProgramNodeHandler::ExternalProgramNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ExternalProgramNodeHandler::~ExternalProgramNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExternalProgramNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, std::ostream& os){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::ExternalProgramNode, pNode);
	const Model::ExternalProgramNode *pExternalProgramNode = IAS_DYNAMICCAST_CONST(Model::ExternalProgramNode, pNode);

	printIndent(pCtx,os);
	os<<"PROGRAM ";
	CallbackRegister::SubCall(pExternalProgramNode->getQualifiedNameNode(),pCtx,os);
	pCtx->iIndent+=5;
	CallbackRegister::SubCall(pExternalProgramNode->getParametersNode(),pCtx,os);
	pCtx->iIndent-=5;
	printIndent(pCtx,os);
	os<<"EXTERNAL \""<<pExternalProgramNode->getLibrary();
	os<<":"<<pExternalProgramNode->getModule();
	os<<":"<<pExternalProgramNode->getSymbol();
	os<<"\"(";

	const StringList& lstParameters(pExternalProgramNode->getParameters());

	for(StringList::const_iterator it=lstParameters.begin(); it != lstParameters.end(); it++){
		if(it !=lstParameters.begin())
			os<<",";
		os<<'"'<<(*it)<<'"';
	}
	os<<");\n";

}
/*************************************************************************/
}
}
}
