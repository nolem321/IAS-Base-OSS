/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathDateExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDateExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDateExpr_H_

#include "XPathExprFamily.h"
#include "../DateExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {
class XPathAccessor;
/*************************************************************************/
/** The class. */
 class XPathDateExpr :
	public DateExpr,
	public XPathExprFamily{
public:

	virtual ~XPathDateExpr() throw();

	virtual ::IAS::Date evaluateDate(Context *pCtx) const;

protected:
	XPathDateExpr(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	friend class ::IAS::Factory<XPathDateExpr>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDateExpr_H_ */
