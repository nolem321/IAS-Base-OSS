/*
 * File: IAS-LangLib/src/lang/export/text/stmt/ReturnNodeHandler.cpp
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
#include "ReturnNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

namespace IAS {
namespace Lang {
namespace Export{
namespace Text {
namespace Stmt {

/*************************************************************************/
ReturnNodeHandler::ReturnNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ReturnNodeHandler::~ReturnNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ReturnNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::ReturnNode, pNode);
	const Model::Stmt::ReturnNode *pReturnNode = IAS_DYNAMICCAST_CONST(Model::Stmt::ReturnNode, pNode);

	printIndent(pCtx, aResult);

	printKeyword(aResult,"RETURN ");
	if(pReturnNode->hasExpression()){
		const Model::Expr::ExprNode*     pExprNode = pReturnNode->getExpressionNode();
		CallbackRegister::SubCall(pExprNode,pCtx,aResult);
	}
}
/*************************************************************************/
}
}
}
}
}
