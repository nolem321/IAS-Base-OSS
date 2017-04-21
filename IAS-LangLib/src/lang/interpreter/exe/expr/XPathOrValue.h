/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/XPathOrValue.h
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
#ifndef _IAS_Lang_Interpreter_Exe_Expr_XPathOrValue_H_
#define _IAS_Lang_Interpreter_Exe_Expr_XPathOrValue_H_

#include "DataObjectExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class BooleanExpr;
namespace XPath{
class XPathExprFamily;
}
/*************************************************************************/
/** The XPathOrValue class.
 *
 */
class XPathOrValue : public virtual DataObjectExpr {

public:

	virtual ~XPathOrValue() throw();

	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const;

protected:
	XPathOrValue(const DM::DataFactory* pDataFactory,
			  XPath::XPathExprFamily* pVarExpr,
			  Expr* pDefault);

	IAS_DFT_FACTORY<XPath::XPathExprFamily>::PtrHolder ptrVarExpr;
	IAS_DFT_FACTORY<Expr>::PtrHolder                   ptrDefault;

	friend class ::IAS::Factory<XPathOrValue>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_Lang_Interpreter_Exe_Expr_XPathOrValue_H_ */
