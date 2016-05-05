/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathDataObjectExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectExpr_H_

#include "XPathExprFamily.h"
#include "../DataObjectExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
class Expr;
namespace XPath {

/*************************************************************************/
/** The class. */
 class XPathDataObjectExpr :
	public virtual DataObjectExpr,
	public virtual XPathExprFamily{
public:

	virtual ~XPathDataObjectExpr() throw();


	virtual void evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const;

protected:
	XPathDataObjectExpr(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	friend class ::IAS::Factory<XPathDataObjectExpr>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectExpr_H_ */
