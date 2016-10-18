/*
 * File: IAS-LangLib/src/lang/interpreter/proc/stmt/ConditionalAssignmentNodeHandler.cpp
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
#include "ConditionalAssignmentNodeHandler.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/allmodel.h>
#include "../CallbackRegister.h"

#include <lang/interpreter/exe/allexe.h>

namespace IAS {
namespace Lang {
namespace Interpreter{
namespace Proc {
namespace Stmt {

/*************************************************************************/
ConditionalAssignmentNodeHandler::ConditionalAssignmentNodeHandler(){
	IAS_TRACER;
}
/*************************************************************************/
ConditionalAssignmentNodeHandler::~ConditionalAssignmentNodeHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ConditionalAssignmentNodeHandler::call(const Model::Node* pNode, CallbackCtx *pCtx, CallbackSignature::Result& aResult){
	IAS_TRACER;

	IAS_TYPEID_CHECK(Model::Stmt::ConditionalAssignmentNode, pNode);
	const Model::Stmt::ConditionalAssignmentNode *pConditionalAssignmentNode = IAS_DYNAMICCAST_CONST(Model::Stmt::ConditionalAssignmentNode, pNode);

	const Model::Expr::XPath::XPathAccessNode*     pXPathAccessNode = pConditionalAssignmentNode->getXPathAccessNode();
	const Model::Stmt::LeftSideNode* pLeftSideNode = pConditionalAssignmentNode->getLeftSideNode();
	
	CallbackSignature::Result aSubCallResult;
	CallbackRegister::SubCall(pLeftSideNode,pCtx,aSubCallResult);
	IAS_DFT_FACTORY<Exe::Stmt::LeftSide>::PtrHolder ptrLeftSide(aSubCallResult.pLeftSide);

	CallbackRegister::SubCall(pXPathAccessNode,pCtx,aSubCallResult);

	IAS_DFT_FACTORY<Exe::Stmt::ConditionalAssignment>::PtrHolder
		ptrConditionalAssignment(IAS_DFT_FACTORY<Exe::Stmt::ConditionalAssignment>::Create(ptrLeftSide.pass(),aSubCallResult.pXPathExprFamily));

	ptrConditionalAssignment->setSourceLine(pConditionalAssignmentNode->getSourceLocation().getLineNumber());

	aResult.pStatement=ptrConditionalAssignment.pass();
}
/*************************************************************************/
}
}
}
}
}
