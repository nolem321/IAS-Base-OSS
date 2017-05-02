/*
 * File: IAS-LangLib/src/lang/model/stmt/IndexNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_IndexNode_H_
#define _IAS_AS_Lang_Model_Stmt_IndexNode_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {

namespace Dec{
class QualifiedNameNode;
}

namespace Expr {
namespace XPath {
 class XPathAccessNode;
}
class ExprNode;

namespace XPath{
class XPathAccessNode;
}
}

namespace Stmt  {

/*************************************************************************/
/** The class. */
 class IndexNode : public StatementNode{
public:

	virtual ~IndexNode() throw();

	const Expr::XPath::XPathAccessNode*            getListXPathAccessNode()    const { return ptrListXPathAccessNode; };
	const Expr::XPath::XPathAccessNode*            getIndexXPathAccessNode()   const { return ptrIndexXPathAccessNode; };

protected:
	IndexNode(Expr::XPath::XPathAccessNode       *pListXPathAccessNode,
			  Expr::XPath::XPathAccessNode       *pIndexXPathAccessNode);

	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder     ptrListXPathAccessNode;
	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder     ptrIndexXPathAccessNode;

	friend class ::IAS::Factory<IndexNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_WITHNODE_H_ */
