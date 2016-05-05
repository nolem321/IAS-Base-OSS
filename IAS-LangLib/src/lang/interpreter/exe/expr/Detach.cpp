/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Detach.cpp
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
#include "Detach.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"
#include "xpath/XPathExprFamily.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
Detach::Detach(XPath::XPathExprFamily *pXPathExprFamily) :
		ptrXPathExprFamily(pXPathExprFamily) {
	IAS_TRACER;
}
/*************************************************************************/
Detach::~Detach() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void Detach::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const {
	IAS_TRACER;

	DM::DataObjectPtr dmTmp;
	ptrXPathExprFamily->evaluate(pCtx,dmTmp);
	ptrXPathExprFamily->deleteDataObject(pCtx);
	if(dmTmp)
		refResult = dmTmp->duplicate();
	else
		refResult = NULL;
}
/*************************************************************************/
void Detach::evaluate(Context *pCtx, IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& refResult) const {
	IAS_TRACER;

	ExprResultSetter aDetachResultSetter(refResult);
	ptrXPathExprFamily->evaluate(pCtx,aDetachResultSetter);
	ptrXPathExprFamily->deleteDataObject(pCtx);
}
/*************************************************************************/
}
}
}
}
}
