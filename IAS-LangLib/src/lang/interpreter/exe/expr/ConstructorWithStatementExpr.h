/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ConstructorWithStatementExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_ConstructorWithStatementExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_ConstructorWithStatementExpr_H_

#include "ConstructorExpr.h"
#include "lang/interpreter/exe/dec/DeclarationBlockFeature.h"
#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt{
class Statement;
}
namespace Expr {
class Expr;

/*************************************************************************/
/** The class. */
 class ConstructorWithStatementExpr :
		 public Dec::DeclarationBlockFeature,
		 public ConstructorExpr{
public:

	virtual ~ConstructorWithStatementExpr()throw();

	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const;

	void setStatement(Stmt::Statement* pStatement);


protected:
	ConstructorWithStatementExpr(const IAS::DM::Type *pType);

	IAS_DFT_FACTORY<Stmt::Statement>::PtrHolder  ptrStatement;

	friend class ::IAS::Factory<ConstructorWithStatementExpr>;
};


/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYExpr_H_ */
