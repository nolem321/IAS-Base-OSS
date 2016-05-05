/*
 * File: IAS-LangLib/src/lang/model/expr/IsNullNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_IsNullNode_H_
#define _IAS_AS_Lang_Model_Expr_IsNullNode_H_

#include "UnaryOperNode.h"
#include "LogicalExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class ExprNode;

namespace XPath{
class XPathAccessNode;
}

/*************************************************************************/
/** The class. */
 class IsNullNode : public LogicalExprNode {
public:

	virtual ~IsNullNode() throw();

	XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };

protected:
	IsNullNode(XPath::XPathAccessNode *pXPathAccessNode);

	IAS_DFT_FACTORY<XPath::XPathAccessNode>::PtrHolder ptrXPathAccessNode;

	friend class ::IAS::Factory<IsNullNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_RelationalEqNODE_H_ */
