/*
 * File: IAS-LangLib/src/lang/model/stmt/CallNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_CallNode_H_
#define _IAS_AS_Lang_Model_Stmt_CallNode_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {

namespace Dec{
class QualifiedNameNode;
}

namespace Expr{
class ExprListNode;
}

namespace Stmt {

class LeftSideNode;

/*************************************************************************/
/** The class. */
 class CallNode : public StatementNode {
public:

	virtual ~CallNode() throw();

	inline Dec::QualifiedNameNode*   getQualifiedNameNode() const { return ptrQualifiedNameNode; };
	inline Expr::ExprListNode*       getExprListNode() const { return ptrExprListNode; };

protected:
	CallNode(Dec::QualifiedNameNode   *pQualifiedNameNode,
			 Expr::ExprListNode       *pExprListNode);

	IAS_DFT_FACTORY<Dec::QualifiedNameNode>::PtrHolder    ptrQualifiedNameNode;
	IAS_DFT_FACTORY<Expr::ExprListNode>::PtrHolder        ptrExprListNode;

	friend class ::IAS::Factory<CallNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Stmt_ASSIGNMENTNODE_H_ */
