/*
 * File: IAS-LangLib/src/lang/model/stmt/WithNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_WITHNODE_H_
#define _IAS_AS_Lang_Model_Stmt_WITHNODE_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {

namespace Expr {
class ExprNode;

namespace XPath{
class XPathAccessNode;
}
}

namespace Stmt  {

/*************************************************************************/
/** The class. */
 class WithNode : public StatementNode{
public:

	virtual ~WithNode() throw();

	const String&                   getVariable()      const { return strVariable; };
	const Expr::XPath::XPathAccessNode*   getVariableExpr()  const { return ptrVarExprNode; };
	Stmt::StatementNode*            getStatementNode() const { return ptrStatementNode; };

	bool hasVariable()const { return strVariable.length() > 0; }

protected:
	WithNode(const String         &strVariable,
			 Expr::XPath::XPathAccessNode       *pVarExprNode,
			 Stmt::StatementNode* pStatementNode);

	const String strVariable;

	IAS_DFT_FACTORY<StatementNode>::PtrHolder          ptrStatementNode;
	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder     ptrVarExprNode;

	friend class ::IAS::Factory<WithNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_WITHNODE_H_ */
