/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ExprList.cpp
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
#include "ExprList.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Expr.h"
#include "ExprResultSetter.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
ExprList::ExprList(int iSize):
		iNumExprs(0){
	IAS_TRACER;
	tabOrderedExprs.resize(iSize);
}
/*************************************************************************/
ExprList::~ExprList() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExprList::addExpr(Expr* pExpr){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pExpr);
	tabOrderedExprs[iNumExprs++]=pExpr;
	phcExpr.addPointer(pExpr);
}
/*************************************************************************/
void ExprList::evaluate(Context *pCtx, DM::DataObjectPtr refHolder, bool bSkipResult) const{
	IAS_TRACER;

	const DM::ComplexType *pComplexType=refHolder->getType()->asComplexType();
	const DM::PropertyList& lstProperties=pComplexType->getProperties();

	if(iNumExprs != tabOrderedExprs.size())
		IAS_THROW(InternalException("iNumExprs != tabOrderedExprs.size()"));

	if(bSkipResult){
		if(iNumExprs != lstProperties.getSize() - 1)
			IAS_THROW(BadUsageException("Wrong number of arguments."));
	}else{
		if(iNumExprs != lstProperties.getSize())
			IAS_THROW(BadUsageException("Wrong number of arguments or the returned cannot be ignored."));
	}


	for(int iIdx=0; iIdx < iNumExprs; iIdx++){

		Expr *pExpr = tabOrderedExprs[iIdx];
		const DM::Property *pProperty = lstProperties.getProperty(iIdx);

		ExprResultSetter aResult(refHolder,pProperty);
		pExpr->evaluate(pCtx,aResult);
	}
}

/*************************************************************************/
}
}
}
}
}
