/*
 * File: IAS-LangLib/src/lang/model/expr/ExprListNode.h
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
#ifndef _IAS_Lang_Model_Expr_ExprListNode_H_
#define _IAS_Lang_Model_Expr_ExprListNode_H_

#include <commonlib/commonlib.h>

#include "../Node.h"
#include <list>

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {

class ExprNode;

/*************************************************************************/
/** The ExprListNode class.
 *
 */
class ExprListNode : public Node {
public:

	virtual ~ExprListNode() throw();

	typedef std::list<const ExprNode*> ExprNodeList;

	void addExprNode(ExprNode *pExprNode);
	const ExprNodeList& getExprNodes() const;

protected:
	ExprListNode();

	ExprNodeList              lstExprNodes;

	IAS_DFT_FACTORY<ExprNode>::PtrHoldersCollection phcExprNodes;

	friend class ::IAS::Factory<ExprListNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Model_Expr_ExprListNode_H_ */
