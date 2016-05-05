/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathDataObjectListExpr.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectListExpr_H_
#define _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectListExpr_H_

#include "../DataObjectListExpr.h"
#include "XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {

/*************************************************************************/
/** The class. */
 class XPathDataObjectListExpr :
	public virtual Expr,
	public virtual DataObjectListExpr,
	public virtual XPathExprFamily{
public:

	virtual ~XPathDataObjectListExpr() throw();

	/** Main evaluation method overloaded.*/
	virtual void evaluate(Context *pCtx,
						  ExprResultSetter& refResult) const;

	virtual bool isArray()const;

protected:
	XPathDataObjectListExpr(Expr* pExpr, XPathAccessor  *pXPathAccessor);

	friend class ::IAS::Factory<XPathDataObjectListExpr>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_AS_Lang_Interpreter_Exe_Expr_XPath_XPathDataObjectListExpr_H_ */
