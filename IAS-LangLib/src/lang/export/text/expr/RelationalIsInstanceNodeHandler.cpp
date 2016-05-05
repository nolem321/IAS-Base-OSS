/*
 * File: IAS-LangLib/src/lang/export/text/expr/RelationalIsInstanceNodeHandler.cpp
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
#include "RelationalIsInstanceNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"
#include "../SourceStore.h"


namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Expr {

/*************************************************************************/
RelationalIsInstanceNodeHandler::RelationalIsInstanceNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
RelationalIsInstanceNodeHandler::~RelationalIsInstanceNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RelationalIsInstanceNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::RelationalIsInstanceNode, pNode);
	const Model::Expr::RelationalIsInstanceNode *pRelationalIsInstanceNode = IAS_DYNAMICCAST_CONST(Model::Expr::RelationalIsInstanceNode, pNode);

	handleUnary(pRelationalIsInstanceNode->getChild(),pCtx,aResult,"");

	aResult.ssOutput<<" ISINSTANCE (";

	aResult.ssOutput<<pRelationalIsInstanceNode->getTypeInfoNode()->getType();

	if(pRelationalIsInstanceNode->getTypeInfoNode()->hasNamespace())
		aResult.ssOutput<<": \""<<pRelationalIsInstanceNode->getTypeInfoNode()->getNamespace() <<"\"";

	aResult.ssOutput<<")";
}
/*************************************************************************/
}
}
}
}
}
