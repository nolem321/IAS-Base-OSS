/*
 * File: IAS-LangLib/src/lang/export/text/expr/CastNodeHandler.cpp
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
#include "CastNodeHandler.h"
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
CastNodeHandler::CastNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CastNodeHandler::~CastNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CastNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::CastNode, pNode);
	const Model::Expr::CastNode *pCastNode = IAS_DYNAMICCAST_CONST(Model::Expr::CastNode, pNode);

	CallbackSignature::Result aResultExpr;
	CallbackRegister::SubCall(pCastNode->getChild(), pCtx, aResultExpr);

	aResult.ssOutput<<" ( ";
	aResult.ssOutput<<aResultExpr.ssOutput.str();
	aResult.ssOutput<<" AS ";
	const Model::Dec::TypeInfoNode *pTypeInfoNode = pCastNode->getTypeInfoNode();
	aResult.ssOutput<<pTypeInfoNode->getType();
	aResult.ssOutput<<" : \""<<pTypeInfoNode->getNamespace()<<"\"";
	aResult.ssOutput<<" ) ";

}
/*************************************************************************/
}
}
}
}
}
