/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathExprAccessNode.cpp
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
#include "XPathExprAccessNode.h"
#include<lang/log/LogLevel.h>
#include "XPathNode.h"
#include "../ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathExprAccessNode::XPathExprAccessNode(ExprNode* pExprNode):
	UnaryOperNode(pExprNode){
	IAS_TRACER;
}
/*************************************************************************/
XPathExprAccessNode::~XPathExprAccessNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
}
