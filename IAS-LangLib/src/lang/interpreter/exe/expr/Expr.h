/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/Expr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_Expr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_Expr_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {
class ExprResultSetter;

/*************************************************************************/
/** Base class for expressions */
/** The class. */
 class Expr {
public:

	virtual ~Expr() throw();

	static Expr* Create();

	/** String evaluation method */
	virtual String evaluateString(Context *pCtx) const =0;

	/** Integer evaluation method */
	virtual int    evaluateInt(Context *pCtx) const =0;

	/** Float evaluation method */
	virtual Float  evaluateFloat(Context *pCtx) const =0;

	/** Boolean evaluation method */
	virtual bool  evaluateBoolean(Context *pCtx) const =0;

	/** DateTime evaluation method */
	virtual ::IAS::DateTime  evaluateDateTime(Context *pCtx) const =0;

	/** Date evaluation method */
	virtual ::IAS::Date      evaluateDate(Context *pCtx) const =0;

	/** Time evaluation method */
	virtual ::IAS::Time      evaluateTime(Context *pCtx) const =0;

	/** Main evaluation method */
	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const =0;

	/** Main evaluation method with a cast.*/
	virtual void evaluate(Context *pCtx, ExprResultSetter& refResult) const;

	//virtual bool isArray()const;

	const DM::Type* getType()const;

protected:
	Expr()throw();

	void setType(const DM::Type* pType);

private:
	const DM::Type* pType;

	friend class ::IAS::Factory<Expr>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_Expr_H_ */
