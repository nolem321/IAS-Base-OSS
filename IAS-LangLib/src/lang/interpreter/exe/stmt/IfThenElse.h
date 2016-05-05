/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/IfThenElse.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_IFTHENELSE_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_IFTHENELSE_H_

#include "Statement.h"

#include "../expr/Expr.h"
#include "../expr/BooleanExpr.h"


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;

namespace Stmt {
class Statement;

/*************************************************************************/
/** The If-Then-Else statement.
 */
/** The class. */
 class IfThenElse : public Statement {
public:

	virtual ~IfThenElse() throw();

	virtual void execute(Context *pCtx) const;

protected:
	IfThenElse(Expr::BooleanExpr *pCondition,
			   Statement         *pThenStatements,
			   Statement         *pElseStatements);

	IAS_DFT_FACTORY<Expr::BooleanExpr>::PtrHolder ptrCondition;
    IAS_DFT_FACTORY<Statement>::PtrHolder         ptrThenStatements;
	IAS_DFT_FACTORY<Statement>::PtrHolder         ptrElseStatements;

	friend class ::IAS::Factory<IfThenElse>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_ASSIGNMENT_H_ */
