/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathExprNode.cpp
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
#include "XPathExprNode.h"
#include<lang/log/LogLevel.h>
#include "XPathNode.h"
#include "XPathAccessNode.h"
#include "../ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathExprNode::XPathExprNode(XPathAccessNode* pXPathAccessNode):
		ptrXPathAccessNode(pXPathAccessNode){
	IAS_TRACER;
}
/*************************************************************************/
XPathExprNode::~XPathExprNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
XPathAccessNode* XPathExprNode::getXPathAccessNode()const{
	IAS_TRACER;
	return ptrXPathAccessNode;
}
/*************************************************************************/
}
}
}
}
}
