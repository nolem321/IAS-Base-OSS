/*
 * File: IAS-LangLib/src/lang/model/expr/ConstructorNode.h
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
#ifndef _IAS_AS_Lang_Model_Expr_ConstructorNode_H_
#define _IAS_AS_Lang_Model_Expr_ConstructorNode_H_

#include <commonlib/commonlib.h>
#include "ExprNode.h"

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt{
class StatementNode;
}
namespace Expr {

/*************************************************************************/
/** The class. */
 class ConstructorNode : public ExprNode{
public:

	virtual ~ConstructorNode() throw();

	inline const String& getTypeName() const { return strName; };
	inline const String& getTypeURI() const { return strURI; };

	bool hasStatement()const{
		return ! ptrStatementNode.isNull();
	}

	Stmt::StatementNode* getStatementNode() const { return ptrStatementNode; };

protected:

	ConstructorNode(const String& strName, const String& strURI, Stmt::StatementNode* ptrStatementNode=0);

	String strURI;
	String strName;

	IAS_DFT_FACTORY<Stmt::StatementNode>::PtrHolder ptrStatementNode;

	friend class ::IAS::Factory<ConstructorNode>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_Expr_CONSTNODE_H_ */
