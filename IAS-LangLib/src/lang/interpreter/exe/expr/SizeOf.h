/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/SizeOf.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_SizeOf_H_
#define _IAS_Lang_Interpreter_Exe_Expr_SizeOf_H_

#include "IntegerExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath{
class XPathExprFamily;
}

/*************************************************************************/
/** The SizeOf class.
 *
 */
class SizeOf : public virtual IntegerExpr {

public:

	virtual ~SizeOf() throw();

	virtual int evaluateInt(Context *pCtx) const;

protected:
	SizeOf(const DM::DataFactory* pDataFactory, XPath::XPathExprFamily* pVarExpr);

	IAS_DFT_FACTORY<XPath::XPathExprFamily>::PtrHolder ptrVarExpr;

	friend class ::IAS::Factory<SizeOf>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_SizeOf_H_ */
