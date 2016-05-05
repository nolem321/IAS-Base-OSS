/*
 * File: IAS-LangLib/src/lang/model/stmt/StatementsListNode.h
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
#ifndef _IAS_AS_Lang_Model_STATEMENTSLISTNODE_H_
#define _IAS_AS_Lang_Model_STATEMENTSLISTNODE_H_

#include <commonlib/commonlib.h>
#include "StatementNode.h"
#include "../dec/DeclarationBlockFeature.h"

#include <list>

namespace IAS {
namespace Lang {
namespace Model {
namespace Stmt {


/*************************************************************************/
/** The class. */
 class StatementsListNode :
		public StatementNode,
		public ::IAS::Lang::Model::Dec::DeclarationBlockFeature {
public:

	typedef std::list<StatementNode*> StatementNodesList;

	void addStatement(StatementNode* pStatement);

	const StatementNodesList& getStatementsListAsConst() const;
	const StatementNodesList& getStatementsList() const;

	virtual ~StatementsListNode() throw();

protected:
	StatementsListNode();

	StatementNodesList                 					 lstStatements;
	IAS_DFT_FACTORY<StatementNode>::PtrHoldersCollection phcStatements;

	friend class ::IAS::Factory<StatementsListNode>;

};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_AS_Lang_Model_STATEMENTSLISTNODE_H_ */
