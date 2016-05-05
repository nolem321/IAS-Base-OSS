/*
 * File: IAS-LangLib/src/lang/model/expr/OperNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_OperNode_H_
#define _IAS_AS_Lang_Model_Expr_OperNode_H_

#include "ExprNode.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class ExprNode;

/*************************************************************************/
/** The class. */
 class OperNode :
	public ExprNode{
public:

	virtual ~OperNode() throw();

	inline ExprNode *getLeftExpr() const { return ptrLeftExprNode; };
	inline ExprNode *getRightExpr() const { return ptrRightExprNode; };

protected:
	OperNode(ExprNode *pLeftExprNode, ExprNode *pRightExprNode);

	IAS_DFT_FACTORY<ExprNode>::PtrHolder ptrLeftExprNode;
	IAS_DFT_FACTORY<ExprNode>::PtrHolder ptrRightExprNode;

	friend class ::IAS::Factory<OperNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_RelationalBinaryOPERNODE_H_ */
