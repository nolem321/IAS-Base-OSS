/*
 * File: IAS-LangLib/src/lang/export/text/stmt/AssignmentNodeHandler.cpp
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
#include "AssignmentNodeHandler.h"
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
AssignmentNodeHandler::AssignmentNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
AssignmentNodeHandler::~AssignmentNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void AssignmentNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::AssignmentNode, pNode);
	const Model::Stmt::AssignmentNode *pAssignmentNode = IAS_DYNAMICCAST_CONST(Model::Stmt::AssignmentNode, pNode);

	const Model::Expr::ExprNode*     pExprNode = pAssignmentNode->getExpressionNode();
	const Model::Stmt::LeftSideNode* pLeftSideNode = pAssignmentNode->getLeftSideNode();

	CallbackRegister::SubCall(pLeftSideNode,pCtx,aResult);
	aResult.ssOutput<<" = ";
	CallbackRegister::SubCall(pExprNode,pCtx,aResult);
}
/*************************************************************************/
}
}
}
}
}
