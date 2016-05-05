/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathStringExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathStringExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathStringExpr_H_

#include "XPathExprFamily.h"
#include "../StringExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class Expr;
namespace XPath {

/*************************************************************************/
/** The class. */
 class XPathStringExpr :
	public StringExpr,
	public XPathExprFamily{
public:

	virtual ~XPathStringExpr() throw();

	virtual String evaluateString(Context *pCtx) const;

protected:
	XPathStringExpr(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	friend class ::IAS::Factory<XPathStringExpr>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathStringExpr_H_ */
