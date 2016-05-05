/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ExprList.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_ExprList_H_
#define _IAS_Lang_Interpreter_Exe_Expr_ExprList_H_

#include <commonlib/commonlib.h>
#include "dm/datamodel.h"
#include <vector>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {
class Expr;

/*************************************************************************/
/** The ExprList class.
 *
 */
class ExprList {
public:

	virtual ~ExprList() throw();

	virtual void evaluate(Context *pCtx,
						  DM::DataObjectPtr refHolder,
						  bool bSkipResult = false) const;

	void addExpr(Expr* pExpr);

	typedef std::vector<Expr*>   OrderedExprTab;

	const OrderedExprTab& getExprVector()const { return tabOrderedExprs; };

protected:
	ExprList(int iSize);

	IAS_DFT_FACTORY<Expr>::PtrHoldersCollection phcExpr;
	OrderedExprTab              				tabOrderedExprs;

	int iNumExprs;
	friend class ::IAS::Factory<ExprList>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_ExprList_H_ */
