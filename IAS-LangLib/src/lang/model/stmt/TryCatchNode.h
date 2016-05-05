/*
 * File: IAS-LangLib/src/lang/model/stmt/TryCatchNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_TryCatchNode_H_
#define _IAS_AS_Lang_Model_Stmt_TryCatchNode_H_

#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {

class StatementNode;
class CatchListNode;

/*************************************************************************/
/** The class. */
 class TryCatchNode :public StatementNode {
public:

	virtual ~TryCatchNode() throw();

	const Stmt::StatementNode* getStatementNode() const { return ptrStatementNode; };
	const Stmt::CatchListNode* getCatchListNode() const { return ptrCatchListNode; };

protected:
	TryCatchNode(Stmt::StatementNode* pStatementNode,
			  	 Stmt::CatchListNode* pCatchListNode);

	IAS_DFT_FACTORY<StatementNode>::PtrHolder      ptrStatementNode;
	IAS_DFT_FACTORY<CatchListNode>::PtrHolder      ptrCatchListNode;

	friend class ::IAS::Factory<TryCatchNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_IFTHENELSENODE_H_ */
