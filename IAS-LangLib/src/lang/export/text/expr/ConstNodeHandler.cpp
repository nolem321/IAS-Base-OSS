/*
 * File: IAS-LangLib/src/lang/export/text/expr/ConstNodeHandler.cpp
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
#include "ConstNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"


namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Expr {

/*************************************************************************/
ConstNodeHandler::ConstNodeHandler(){
	IAS_TRACER;
}

/*************************************************************************/
ConstNodeHandler::~ConstNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ConstNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ConstNode, pNode);
	const Model::Expr::ConstNode *pConstNode = IAS_DYNAMICCAST_CONST(Model::Expr::ConstNode, pNode);

	if(pConstNode->getType() == Model::Expr::ConstNode::CN_STRING)
		aResult.ssOutput<<"\"";

	aResult.ssOutput<<pConstNode->getOriginalText();

	if(pConstNode->getType() == Model::Expr::ConstNode::CN_STRING)
		aResult.ssOutput<<"\"";


}
/*************************************************************************/
}
}
}
}
}
