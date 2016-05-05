/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/ForLoop.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_ForLoop_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_ForLoop_H_

#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr{
class BooleanExpr;
}
namespace Stmt {
class Statement;

/*************************************************************************/
/** The class. */
 class ForLoop : public Statement {
public:

	virtual ~ForLoop() throw();

	virtual void execute(Context *pCtx) const;

protected:
	ForLoop(Expr::BooleanExpr *pCondition,
			Statement         *pStatements,
			Statement         *pStartStatement,
			Statement         *pStepStatement);

	IAS_DFT_FACTORY<Expr::BooleanExpr>::PtrHolder ptrCondition;
	IAS_DFT_FACTORY<Statement>::PtrHolder         ptrStatements;

	IAS_DFT_FACTORY<Statement>::PtrHolder         ptrStartStatement;
	IAS_DFT_FACTORY<Statement>::PtrHolder         ptrStepStatement;

	friend class ::IAS::Factory<ForLoop>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_ForLoop_H_ */
