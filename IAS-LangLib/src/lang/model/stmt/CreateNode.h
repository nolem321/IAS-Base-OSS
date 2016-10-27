/*
 * File: IAS-LangLib/src/lang/model/stmt/CreateNode.h
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
#ifndef _IAS_AS_Lang_Model_Stmt_CreateNode_H_
#define _IAS_AS_Lang_Model_Stmt_CreateNode_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Expr{
namespace XPath{
class XPathAccessNode;
}
}
namespace Stmt {

/*************************************************************************/
/** The class. */
 class CreateNode : public StatementNode {
public:

	virtual ~CreateNode() throw();

	inline Expr::XPath::XPathAccessNode* getXPathAccessNode() const { return ptrXPathAccessNode; };
	Stmt::StatementNode*            getStatementNode() const { return ptrStatementNode; };

	bool hasStatement()const{
		return ! ptrStatementNode.isNull();
	}

protected:
	CreateNode(Expr::XPath::XPathAccessNode *pXPathAccessNode, Stmt::StatementNode* pStatementNode=0);

	IAS_DFT_FACTORY<Expr::XPath::XPathAccessNode>::PtrHolder  ptrXPathAccessNode;
	IAS_DFT_FACTORY<StatementNode>::PtrHolder          ptrStatementNode;

	friend class ::IAS::Factory<CreateNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Stmt_ASSIGNMENTNODE_H_ */
