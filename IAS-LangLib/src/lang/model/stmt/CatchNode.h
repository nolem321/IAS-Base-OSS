/*
 * File: IAS-LangLib/src/lang/model/stmt/CatchNode.h
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
#ifndef _IAS_Lang_Model_Stmt_CatchNode_H_
#define _IAS_Lang_Model_Stmt_CatchNode_H_

#include "../Node.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Lang {
namespace Model {
namespace Dec{
class DeclarationNode;
}
namespace Stmt {
class StatementNode;
/*************************************************************************/
/** The CatchNode class.
 *
 */
class CatchNode : public Node{
public:

	virtual ~CatchNode() throw();

	const Dec::DeclarationNode* getDeclarationNode() const { return ptrDeclarationNode; }
	const Stmt::StatementNode*  getStatementNode()   const { return ptrStatementNode; }


protected:
	CatchNode(Dec::DeclarationNode* pDeclarationNode,
			  Stmt::StatementNode*  pStatementNode);

	IAS_DFT_FACTORY<Dec::DeclarationNode>::PtrHolder  ptrDeclarationNode;
	IAS_DFT_FACTORY<Stmt::StatementNode>::PtrHolder   ptrStatementNode;

	friend class ::IAS::Factory<CatchNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_Lang_Model_Stmt_CatchNode_H_ */
