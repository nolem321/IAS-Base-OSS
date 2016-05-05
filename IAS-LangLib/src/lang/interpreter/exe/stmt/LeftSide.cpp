/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/LeftSide.cpp
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
#include "LeftSide.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "../expr/Expr.h"
#include "../expr/ExprResultSetter.h"
#include "../expr/xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
LeftSide::LeftSide(Expr::XPath::XPathExprFamily *pXPathExprFamily):
				ptrXPathExprFamily(pXPathExprFamily){
	IAS_TRACER;
}
/*************************************************************************/
LeftSide::~LeftSide() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void LeftSide::assignValue(Context *pCtx, Expr::Expr* pExpr) const{
	IAS_TRACER;

	Expr::ExprResultSetter aResult(ptrXPathExprFamily->getTargetObjectSetter(pCtx));
	pExpr->evaluate(pCtx,aResult);

}
/*************************************************************************/
}
}
}
}
}
