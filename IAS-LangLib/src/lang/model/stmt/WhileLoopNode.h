/*
 * File: IAS-LangLib/src/lang/model/stmt/WhileLoopNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_WHILELOOPNODE_H_
#define _IAS_AS_Lang_Model_Stmt_WHILELOOPNODE_H_

#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr{
class LogicalExprNode;
}
namespace Stmt {

/*************************************************************************/
/** The class. */
 class WhileLoopNode :public StatementNode{
public:

	virtual ~WhileLoopNode() throw();

	Expr::LogicalExprNode* getLogicalExprNode() const { return ptrLogicalExprNode; };
	Stmt::StatementNode* getStatementNode() const { return ptrStatementNode; };


protected:
	WhileLoopNode(Expr::LogicalExprNode* pLogicalExprNode,
			   	  Stmt::StatementNode* pStatementNode);

	IAS_DFT_FACTORY<Expr::LogicalExprNode>::PtrHolder     ptrLogicalExprNode;
	IAS_DFT_FACTORY<StatementNode>::PtrHolder      ptrStatementNode;

	friend class ::IAS::Factory<WhileLoopNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_WHILELOOPNODE_H_ */
