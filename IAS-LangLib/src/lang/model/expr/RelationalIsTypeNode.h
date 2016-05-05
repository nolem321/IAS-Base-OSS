/*
 * File: IAS-LangLib/src/lang/model/expr/RelationalIsTypeNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_RelationalIsTypeNode_H_
#define _IAS_AS_Lang_Model_Expr_RelationalIsTypeNode_H_

#include "UnaryOperNode.h"
#include "LogicalExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec {
class TypeInfoNode;
}
namespace Expr {
class ExprNode;

/*************************************************************************/
/** The class. */
 class RelationalIsTypeNode : public UnaryOperNode, public LogicalExprNode {
public:

	virtual ~RelationalIsTypeNode() throw();

	const Dec::TypeInfoNode *getTypeInfoNode()const { return ptrTypeInfoNode; }

protected:
	RelationalIsTypeNode(ExprNode *pExprNode, Dec::TypeInfoNode *pTypeInfoNode);

	IAS_DFT_FACTORY<Dec::TypeInfoNode>::PtrHolder ptrTypeInfoNode;

	friend class ::IAS::Factory<RelationalIsTypeNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_RelationalEqNODE_H_ */
