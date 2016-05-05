/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/CopyOf.cpp
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
#include "CopyOf.h"
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
CopyOf::CopyOf(XPath::XPathExprFamily *pXPathExprFamily) :
		ptrXPathExprFamily(pXPathExprFamily) {
	IAS_TRACER;
}
/*************************************************************************/
CopyOf::~CopyOf() throw () {
	IAS_TRACER;
}
/*************************************************************************/
CopyOf::ExprResultSetter::ExprResultSetter(
		const IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& other) :
		IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter(other) {
}
;
/*************************************************************************/
void CopyOf::ExprResultSetter::assign(DM::DataObject* dmValue) {
	IAS_TRACER;
	if(pProperty->isMulti() && iIdx >= 0) {
		ptrDM->getList(pProperty).set(iIdx, dmValue ? dmValue->duplicate() : NULL);
	} else {
		ptrDM->setDataObject(pProperty,dmValue ? dmValue->duplicate() : NULL);
	}
}
/*************************************************************************/
void CopyOf::ExprResultSetter::assignList(DM::DataObjectList& refList) {

	IAS_TRACER;

	if(iIdx > 0)
		IAS_THROW(InternalException(String("Cannot assign array to the other array element.")+=pProperty->getName()));

	DM::DataObjectList& refTargetList=ptrDM->getList(pProperty);
	refTargetList.clear();

	for(int iIdx=0;iIdx<refList.size();iIdx++) {
		DM::DataObject *dmValue(refList.at(iIdx));
		refTargetList.add(dmValue ? refList.at(iIdx)->duplicate() : NULL);
	}
}
/*************************************************************************/
void CopyOf::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const {
	IAS_TRACER;

	DM::DataObjectPtr dmTmp;
	ptrXPathExprFamily->evaluate(pCtx,dmTmp);

	if(!dmTmp.isNull())
		refResult = dmTmp->duplicate();
	else
		refResult = NULL;
}
/*************************************************************************/
void CopyOf::evaluate(Context *pCtx, IAS::Lang::Interpreter::Exe::Expr::ExprResultSetter& refResult) const {
	IAS_TRACER;

	ExprResultSetter aCopyOfResultSetter(refResult);
	ptrXPathExprFamily->evaluate(pCtx,aCopyOfResultSetter);

}
/*************************************************************************/
}
}
}
}
}
