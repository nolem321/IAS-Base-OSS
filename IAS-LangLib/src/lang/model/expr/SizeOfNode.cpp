/*
 * File: IAS-LangLib/src/lang/model/expr/SizeOfNode.cpp
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
#include "SizeOfNode.h"
#include<lang/log/LogLevel.h>
#include "xpath/XPathNode.h"
#include "ExprNode.h"
#include "xpath/XPathAccessNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

/*************************************************************************/
SizeOfNode::SizeOfNode(XPath::XPathAccessNode* pXPathAccessNode):
		ptrXPathAccessNode(pXPathAccessNode){
	IAS_TRACER;
}
/*************************************************************************/
SizeOfNode::~SizeOfNode() throw(){
	IAS_TRACER;
}
/*************************************************************************/
XPath::XPathAccessNode* SizeOfNode::getXPathAccessNode()const{
	IAS_TRACER;
	return ptrXPathAccessNode;
}
/*************************************************************************/
}
}
}
}
