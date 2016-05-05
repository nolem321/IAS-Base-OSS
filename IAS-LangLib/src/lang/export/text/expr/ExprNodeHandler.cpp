/*
 * File: IAS-LangLib/src/lang/export/text/expr/ExprNodeHandler.cpp
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
#include "ExprNodeHandler.h"
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
ExprNodeHandler::ExprNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ExprNodeHandler::~ExprNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExprNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ExprNode, pNode);
	const Model::Expr::ExprNode *pExprNode = IAS_DYNAMICCAST_CONST(Model::Expr::ExprNode, pNode);

}
/*************************************************************************/
void ExprNodeHandler::handleUnary(const Model::Expr::ExprNode* pExprNode,
									  CallbackCtx *pCtx, CallbackSignature::Result& aResult,
								      const String& strText){
	IAS_TRACER;

	printKeyword(aResult,strText);
	CallbackRegister::SubCall(pExprNode,pCtx,aResult);
}
/*************************************************************************/
void ExprNodeHandler::handleBinary(const Model::Expr::ExprNode* pLeftExprNode,
									  const Model::Expr::ExprNode* pRightExprNode,
									  CallbackCtx *pCtx, CallbackSignature::Result& aResult,
								      const String& strText){
	IAS_TRACER;


	aResult.ssOutput<<"(";
	CallbackRegister::SubCall(pLeftExprNode,pCtx,aResult);
	aResult.ssOutput<<strText;
	CallbackRegister::SubCall(pRightExprNode,pCtx,aResult);
	aResult.ssOutput<<")";
}
/*************************************************************************/
}
}
}
}
}
