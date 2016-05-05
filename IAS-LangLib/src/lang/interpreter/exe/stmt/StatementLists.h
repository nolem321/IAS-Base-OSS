/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/StatementLists.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENTLISTS_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENTLISTS_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "Statement.h"

#include "../dec/DeclarationBlockFeature.h"
#include <list>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
/** The class. */
 class StatementLists :
		public Statement,
		public ::IAS::Lang::Interpreter::Exe::Dec::DeclarationBlockFeature{
public:

	virtual ~StatementLists() throw();

	void addStatement(Statement* pStatement);

	virtual void execute(Context *pCtx) const;

protected:
	StatementLists()throw();

	typedef std::list<Statement*>      StatementList;
	StatementList                       lstStatements;
	IAS_DFT_FACTORY<Statement>::PtrHoldersCollection     phcStatements;

	friend class ::IAS::Factory<StatementLists>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_STATEMENTLISTS_H_ */
