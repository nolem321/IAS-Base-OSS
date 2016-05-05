/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/LeftSide.h
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
#ifndef _IAS_AS_Lang_Interpreter_Exe_Stmt_LEFTSIDE_H_
#define _IAS_AS_Lang_Interpreter_Exe_Stmt_LEFTSIDE_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
class Context;
namespace Expr {
class Expr;
namespace XPath{
class XPathExprFamily;
}
}
namespace Stmt {

/*************************************************************************/
/** The left side (assignable) entity.
 * This object holds the left side details (variable, xpath etc.) and
 * the expression to be evaluated upon the execution.
 */
 class LeftSide {
public:

	virtual ~LeftSide() throw();

	void assignValue(Context *pCtx, Expr::Expr* pExpr) const;

protected:
	LeftSide(Expr::XPath::XPathExprFamily   *pXPathExprFamily);

	IAS_DFT_FACTORY<Expr::XPath::XPathExprFamily>::PtrHolder   ptrXPathExprFamily;

	friend class ::IAS::Factory<LeftSide>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_AS_Lang_Interpreter_Exe_Stmt_LEFTSIDE_H_ */
