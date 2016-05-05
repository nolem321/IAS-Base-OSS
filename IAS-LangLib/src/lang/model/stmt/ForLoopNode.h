/*
 * File: IAS-LangLib/src/lang/model/stmt/ForLoopNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_FORLOOPNODE_H_
#define _IAS_AS_Lang_Model_Stmt_FORLOOPNODE_H_

#include "StatementNode.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr {
class ExprNode;
namespace XPath{
class XPathAccessNode;
}
}
namespace Stmt {

/*************************************************************************/
/** The class. */
 class ForLoopNode : public StatementNode{
public:

	virtual ~ForLoopNode() throw();

	Stmt::StatementNode* getStatementNode() const { return ptrStatementNode; };

	Expr::XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };

	Expr::ExprNode* getStartExprNode() const { return ptrStartExprNode; };
	Expr::ExprNode* getStopExprNode()  const { return ptrStopExprNode;  };
	Expr::ExprNode* getStepExprNode()  const { return ptrStepExprNode;  };

	bool hasStepNode() const;

protected:
	ForLoopNode(Expr::XPath::XPathAccessNode *pXPathAccessNode,
				Stmt::StatementNode *pStatementNode,
				Expr::ExprNode     *pStartExprNode,
				Expr::ExprNode     *pStopExprNode,
				Expr::ExprNode     *pStepExprNode);

	ForLoopNode(Expr::XPath::XPathAccessNode *pXPathAccessNode,
					Stmt::StatementNode *pStatementNode,
					Expr::ExprNode     *pStartExprNode,
					Expr::ExprNode     *pStopExprNode);

	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder ptrXPathAccessNode;
	IAS_DFT_FACTORY<StatementNode> ::PtrHolder     ptrStatementNode;

	IAS_DFT_FACTORY<Expr::ExprNode>::PtrHolder     ptrStartExprNode;
	IAS_DFT_FACTORY<Expr::ExprNode>::PtrHolder     ptrStopExprNode;
	IAS_DFT_FACTORY<Expr::ExprNode>::PtrHolder     ptrStepExprNode;


	friend class ::IAS::Factory<ForLoopNode>;

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_FORLOOPNODE_H_ */
