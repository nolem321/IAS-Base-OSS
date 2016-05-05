/*
 * File: IAS-LangLib/src/lang/model/stmt/WithNode.cpp
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
#include "WithNode.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../expr/xpath/XPathAccessNode.h"

#include "../expr/ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {

/*************************************************************************/
WithNode::WithNode(const String             &strVariable,
		 	 	 	Expr::XPath::XPathAccessNode       *pVarExprNode,
		 	 	 	Stmt::StatementNode*     pStatementNode):
		strVariable(strVariable),
		ptrVarExprNode(pVarExprNode),
        ptrStatementNode(pStatementNode){
	IAS_TRACER;
}
/*************************************************************************/
WithNode::~WithNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
