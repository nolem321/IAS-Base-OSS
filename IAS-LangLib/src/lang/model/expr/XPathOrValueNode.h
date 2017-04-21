/*
 * File: IAS-LangLib/src/lang/model/expr/XPathOrValueNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_XPathOrValueNode_H_
#define _IAS_AS_Lang_Model_Expr_XPathOrValueNode_H_

#include "UnaryOperNode.h"
#include "ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath{
class XPathAccessNode;
}

class LogicalExprNode;

/*************************************************************************/
/** The class. */
 class XPathOrValueNode : public ExprNode {
public:

	virtual ~XPathOrValueNode() throw();

	XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };

	Expr::ExprNode* getExprDefaultNode() const { return ptrExprDefaultNode; };

protected:

	XPathOrValueNode(XPath::XPathAccessNode *pXPathAccessNode,
			         ExprNode* pExprDefaultNode);

	IAS_DFT_FACTORY<XPath::XPathAccessNode>::PtrHolder ptrXPathAccessNode;
	IAS_DFT_FACTORY<ExprNode>::PtrHolder ptrExprDefaultNode;

	friend class ::IAS::Factory<XPathOrValueNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_RelationalEqNODE_H_ */
