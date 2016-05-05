/*
 * File: IAS-LangLib/src/lang/model/expr/FunCallNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_FunCallNode_H_
#define _IAS_AS_Lang_Model_Expr_FunCallNode_H_

#include <commonlib/commonlib.h>
#include "ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {

namespace Dec{
class QualifiedNameNode;
}

namespace Expr {

class ExprListNode;


/*************************************************************************/
/** The class. */
 class FunCallNode : public ExprNode {
public:

	virtual ~FunCallNode() throw();


	inline Dec::QualifiedNameNode*   getQualifiedNameNode() const { return ptrQualifiedNameNode; };
	inline Expr::ExprListNode*       getExprListNode() const { return ptrExprListNode; };

protected:
	FunCallNode(Dec::QualifiedNameNode   *pQualifiedNameNode,
			    Expr::ExprListNode       *pExprListNode);

	IAS_DFT_FACTORY<Dec::QualifiedNameNode>::PtrHolder    ptrQualifiedNameNode;
	IAS_DFT_FACTORY<Expr::ExprListNode>::PtrHolder        ptrExprListNode;

	friend class ::IAS::Factory<FunCallNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_ASSIGNMENTNODE_H_ */
