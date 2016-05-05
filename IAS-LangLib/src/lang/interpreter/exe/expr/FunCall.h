/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/FunCall.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_FunCall_H_
#define _IAS_Lang_Interpreter_Exe_Expr_FunCall_H_

#include "Expr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Program;
namespace Expr {
class ExprList;
/*************************************************************************/
/** The FunCall class.
 *
 */
class FunCall : public virtual Expr {
public:

	virtual ~FunCall() throw();

	static Expr* Create(Program* pProgram, ExprList* pExprList);

protected:
	FunCall(Program* pProgram, ExprList* pExprList);
	Program* pProgram;

	IAS_DFT_FACTORY<ExprList>::PtrHolder ptrExprList;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_FunCall_H_ */
