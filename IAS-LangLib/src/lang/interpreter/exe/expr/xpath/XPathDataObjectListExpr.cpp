/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/xpath/XPathDataObjectListExpr.cpp
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
#include "XPathDataObjectListExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/model/allmodel.h>
#include "XPathAccessor.h"
#include "../../Context.h"
#include "../ExprResultSetter.h"
namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {
namespace XPath {
/*************************************************************************/
XPathDataObjectListExpr::XPathDataObjectListExpr(Expr* pExpr,XPathAccessor  *pXPathAccessor):
		XPathExprFamily(pExpr,pXPathAccessor){
	IAS_TRACER;
}
/*************************************************************************/
XPathDataObjectListExpr::~XPathDataObjectListExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool XPathDataObjectListExpr::isArray() const{
	IAS_TRACER;
	return true;
}
/*************************************************************************/
void XPathDataObjectListExpr::evaluate(Context *pCtx, ExprResultSetter& refResult) const{

	IAS_TRACER;

	if(refResult.getProperty()->isMulti()){
		refResult.assignList(getTargetObjectList(pCtx));
	}else{
		String strMsg("Target property is not a list in XPathDataObjectListExpr::evaluate.  ");
		strMsg+=refResult.getProperty()->getName();
		IAS_THROW(InternalException(strMsg));
	}
}
/*************************************************************************/
}
}
}
}
}
}
