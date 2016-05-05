/*
 * File: IAS-LangLib/src/lang/export/text/expr/ExprListNodeHandler.cpp
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
#include "ExprListNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"


namespace IAS {
namespace Lang {
namespace Export {
namespace Text {
namespace Expr {

/*************************************************************************/
ExprListNodeHandler::ExprListNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ExprListNodeHandler::~ExprListNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExprListNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Expr::ExprListNode, pNode);

	const Model::Expr::ExprListNode *pExprListNode = IAS_DYNAMICCAST_CONST(Model::Expr::ExprListNode, pNode);
	const Model::Expr::ExprListNode::ExprNodeList& lstExprNodes = pExprListNode->getExprNodes();

	for(Model::Expr::ExprListNode::ExprNodeList::const_iterator it = lstExprNodes.begin();
		it != lstExprNodes.end();
		it++){

		CallbackSignature::Result aResultExpr;
		CallbackRegister::SubCall((*it),pCtx,aResultExpr);

		if( it != lstExprNodes.begin() )
			aResult.ssOutput<<",";

		aResult.ssOutput<<aResultExpr.ssOutput.str();
	}
}
/*************************************************************************/
}
}
}
}
}
