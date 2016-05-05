/*
 * File: IAS-LangLib/src/lang/model/stmt/IfThenElseNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_IFTHENELSENODE_H_
#define _IAS_AS_Lang_Model_Stmt_IFTHENELSENODE_H_

#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr{
class ExprNode;
}
namespace Stmt {

/*************************************************************************/
/** The class. */
 class IfThenElseNode :public StatementNode {
public:

	virtual ~IfThenElseNode() throw();

	Expr::ExprNode* getExprNode() const { return ptrExprNode; };

	Stmt::StatementNode* getThenStatementNode() const { return ptrThenStatementNode; };
	Stmt::StatementNode* getElseStatementNode() const { return ptrElseStatementNode; };

	bool hasElseStatementNode() const;

protected:
	IfThenElseNode( Expr::ExprNode* pExprNode,
					Stmt::StatementNode* pThenStatementNode,
					Stmt::StatementNode* pElseStatementNode);

	IfThenElseNode( Expr::ExprNode* pExprNode,
					Stmt::StatementNode* pThenStatementNode);

	IAS_DFT_FACTORY<Expr::ExprNode>::PtrHolder     ptrExprNode;

	IAS_DFT_FACTORY<StatementNode>::PtrHolder      ptrThenStatementNode;
	IAS_DFT_FACTORY<StatementNode>::PtrHolder      ptrElseStatementNode;

	friend class ::IAS::Factory<IfThenElseNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_IFTHENELSENODE_H_ */
