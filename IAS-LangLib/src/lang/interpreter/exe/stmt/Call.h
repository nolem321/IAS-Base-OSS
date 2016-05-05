/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Call.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Stmt_Call_H_
#define _IAS_Lang_Interpreter_Exe_Stmt_Call_H_

#include "Statement.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
class Program;
namespace Expr{
class ExprList;
}
namespace Stmt {

/*************************************************************************/
/** The Call class.
 *
 */
class Call : public Statement {
public:

	virtual ~Call() throw();

	virtual void execute(Exe::Context *pCtx)const;

protected:
	Call(Program* pProgram, Expr::ExprList* pExprList);

	Program* pProgram;
	IAS_DFT_FACTORY<Expr::ExprList>::PtrHolder ptrExprList;
	friend class ::IAS::Factory<Call>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Stmt_Call_H_ */
