/*
 * File: IAS-LangLib/src/lang/export/text/expr/CondValueNodeHandler.cpp
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
#include "CondValueNodeHandler.h"
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
CondValueNodeHandler::CondValueNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
CondValueNodeHandler::~CondValueNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CondValueNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::CondValueNode, pNode);
	const  Model::Expr::CondValueNode *pCondValueNode = IAS_DYNAMICCAST_CONST(Model::Expr::CondValueNode, pNode);

	aResult.ssOutput<<"(";
	CallbackRegister::SubCall(pCondValueNode->getExprNode(),pCtx,aResult);
	aResult.ssOutput<<" ? ";
	CallbackRegister::SubCall(pCondValueNode->getExprTrueNode(),pCtx,aResult);
	aResult.ssOutput<<" : ";
	CallbackRegister::SubCall(pCondValueNode->getExprFalseNode(),pCtx,aResult);
	aResult.ssOutput<<")";

}
/*************************************************************************/
}
}
}
}
}
