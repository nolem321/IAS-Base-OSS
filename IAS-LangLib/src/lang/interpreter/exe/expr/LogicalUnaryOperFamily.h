/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/LogicalUnaryOperFamily.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_LogicalUnaryOperFamily_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_LogicalUnaryOperFamily_H_

#include "Expr.h"
#include "BooleanExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class BooleanExpr;

/*************************************************************************/
/** The class. */
 class LogicalUnaryOperFamily : public BooleanExpr{
public:

	virtual ~LogicalUnaryOperFamily() throw();

	static BooleanExpr* Create(const DM::DataFactory* pDataFactory, BooleanExpr* pChild, TypeInfoProxy aTypeInfoProxy);

protected:
	LogicalUnaryOperFamily(const DM::DataFactory* pDataFactory,BooleanExpr* pChild);

	IAS_DFT_FACTORY<BooleanExpr>::PtrHolder ptrChild;
	friend class ::IAS::Factory<LogicalUnaryOperFamily>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_BINARYExpr_H_ */
