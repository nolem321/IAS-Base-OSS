/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/ConditionalAssignment.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_ConditionalAssignment_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_ConditionalAssignment_H_

#include "Statement.h"

#include "../expr/Expr.h"


namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {
namespace XPath{
class XPathExprFamily;
}
}
namespace Stmt {
class LeftSide;

/*************************************************************************/
/** The assignment statement.
 * This class utilizes the LeftSide class.
 */
 class ConditionalAssignment : public Statement {
public:

	virtual ~ConditionalAssignment() throw();

	virtual void execute(Context *pCtx) const;

protected:
	ConditionalAssignment(LeftSide *pLeftSide, Expr::XPath::XPathExprFamily* pVarExpr);

	IAS_DFT_FACTORY<Expr::XPath::XPathExprFamily>::PtrHolder ptrVarExpr;

	IAS_DFT_FACTORY<LeftSide>::PtrHolder   ptrLeftSide;

	friend class ::IAS::Factory<ConditionalAssignment>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_ASSIGNMENT_H_ */
