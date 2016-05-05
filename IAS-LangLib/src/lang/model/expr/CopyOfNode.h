/*
 * File: IAS-LangLib/src/lang/model/expr/CopyOfNode.h
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
#ifndef _IAS_Lang_Model_Expr_CopyOfNode_H_
#define _IAS_Lang_Model_Expr_CopyOfNode_H_

#include "ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
namespace XPath{
class XPathAccessNode;
}
/*************************************************************************/
/** The CopyOfNode class.
 *
 */
class CopyOfNode : public ExprNode {
public:

	virtual ~CopyOfNode() throw();

	inline XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };

protected:
	CopyOfNode(XPath::XPathAccessNode *pXPathAccessNode);

	IAS_DFT_FACTORY<XPath::XPathAccessNode>::PtrHolder  ptrXPathAccessNode;

	friend class ::IAS::Factory<CopyOfNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Model_Expr_CopyOfNode_H_ */
