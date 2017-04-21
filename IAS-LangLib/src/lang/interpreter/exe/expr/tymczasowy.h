/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/tymczasowy.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_tymczasowy_H_
#define _IAS_Lang_Interpreter_Exe_Expr_tymczasowy_H_

#include "DataObjectExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class BooleanExpr;

/*************************************************************************/
/** The tymczasowy class.
 *
 */
class tymczasowy : public virtual DataObjectExpr {

public:

	virtual ~tymczasowy() throw();

	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const;

protected:
	tymczasowy(const DM::DataFactory*  pDataFactory,
			     BooleanExpr      *pCondition,
			     Expr* pExprTrue,
				 Expr* pExprFalse);

	IAS_DFT_FACTORY<BooleanExpr>::PtrHolder            ptrCondition;
	IAS_DFT_FACTORY<Expr>::PtrHolder                   ptrExprTrue;
	IAS_DFT_FACTORY<Expr>::PtrHolder                   ptrExprFalse;

	friend class ::IAS::Factory<tymczasowy>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_tymczasowy_H_ */
