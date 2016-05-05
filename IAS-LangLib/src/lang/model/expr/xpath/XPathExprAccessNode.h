/*
 * File: IAS-LangLib/src/lang/model/expr/xpath/XPathExprAccessNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_XPath_ExprAccessNode_H_
#define _IAS_AS_Lang_Model_Expr_XPath_ExprAccessNode_H_

#include <commonlib/commonlib.h>

#include "XPathAccessNode.h"
#include "../UnaryOperNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath {


class XPathNode;

/*************************************************************************/
/** The class. */
 class XPathExprAccessNode : public XPathRootNode, public UnaryOperNode {
public:

	virtual ~XPathExprAccessNode() throw();


protected:
	XPathExprAccessNode(ExprNode* pExprNode);

	friend class ::IAS::Factory<XPathExprAccessNode>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_AS_Lang_Model_Expr_VARIABLENODE_H_ */
