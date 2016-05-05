/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DataObjectExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_DataObjectExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_DataObjectExpr_H_

#include "Expr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {

/*************************************************************************/
/** The class. */
 class DataObjectExpr : public virtual Expr {
public:

	virtual ~DataObjectExpr() throw();


	virtual String evaluateString(Context *pCtx) const;
	virtual Float  evaluateFloat(Context *pCtx) const;
	virtual int    evaluateInt(Context *pCtx) const;
	virtual bool   evaluateBoolean(Context *pCtx) const;
	virtual ::IAS::DateTime evaluateDateTime(Context *pCtx) const;
	virtual ::IAS::Date evaluateDate(Context *pCtx) const;
	virtual ::IAS::Time evaluateTime(Context *pCtx) const;

protected:
	DataObjectExpr()throw();

	friend class ::IAS::Factory<DataObjectExpr>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_STRINGEXPR_H_ */
