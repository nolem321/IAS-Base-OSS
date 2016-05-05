/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathIntegerExpr.cpp
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
#include "XPathIntegerExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>
#include "XPathAccessor.h"
#include "../../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathIntegerExpr::XPathIntegerExpr(Expr* pExpr,XPathAccessor  *pXPathAccessor):
		XPathExprFamily(pExpr,pXPathAccessor){
	IAS_TRACER;
}
/*************************************************************************/
XPathIntegerExpr::~XPathIntegerExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int XPathIntegerExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;

	int iResult =  getTargetObject(pCtx)->toInteger();
	IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isInfo(),"="<<iResult);
	return iResult;
}
/*************************************************************************/
}
}
}
}
}
}
