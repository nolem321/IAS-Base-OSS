/*
 * File: IAS-LangLib/src/lang/model/stmt/AssignmentNode.cpp
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
#include "AssignmentNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "LeftSideNode.h"
#include "../expr/ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {

/*************************************************************************/
AssignmentNode::AssignmentNode(LeftSideNode   *pLeftSideNode,
	     	 	 	 	 	   Expr::ExprNode  *pExpressionNode){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pLeftSideNode);
	IAS_CHECK_IF_VALID(pExpressionNode);

	this->ptrLeftSideNode=pLeftSideNode;
	this->ptrExpressionNode=pExpressionNode;
}
/*************************************************************************/
AssignmentNode::~AssignmentNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
