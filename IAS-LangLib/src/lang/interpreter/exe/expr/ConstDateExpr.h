/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ConstDateExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_ConstDateExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_ConstDateExpr_H_

#include "ConstExprFamily.h"
#include "DateExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
/** The class. */
 class ConstDateExpr :
	public DateExpr,
	public ConstExprFamily{
public:

	virtual ~ConstDateExpr() throw();

	virtual ::IAS::Date evaluateDate(Context *pCtx) const;

protected:
	ConstDateExpr(const ::IAS::Date& tValue);

	::IAS::Date tValue;
	friend class ::IAS::Factory<ConstDateExpr>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYSTRINGExpr_H_ */
