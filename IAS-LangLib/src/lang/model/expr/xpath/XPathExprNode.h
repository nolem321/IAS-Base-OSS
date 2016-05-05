/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathExprNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_XPath_ExprNode_H_
#define _IAS_AS_Lang_Model_Expr_XPath_ExprNode_H_

#include <commonlib/commonlib.h>
#include "../ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath {

class XPathAccessNode;

/*************************************************************************/
/** The class. */
 class XPathExprNode : public Expr::ExprNode {
public:

	virtual ~XPathExprNode() throw();

	XPathAccessNode* getXPathAccessNode()const;

protected:
	XPathExprNode(XPathAccessNode* pXPathAccessNode);

	IAS_DFT_FACTORY<XPathAccessNode>::PtrHolder ptrXPathAccessNode;

	friend class ::IAS::Factory<XPathExprNode>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_AS_Lang_Model_Expr_VARIABLENODE_H_ */
