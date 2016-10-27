/*
 * File: IAS-LangLib/src/lang/interpreter/exe/stmt/Sort.cpp
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
#include "Sort.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "../Context.h"
#include "../Program.h"
#include "../ProgramContext.h"

#include "../expr/xpath/XPathExprFamily.h"
#include "../expr/xpath/XPathAccessor.h"
#include "Statement.h"
#include "LeftSide.h"
#include "../exception/NullObjectReferenceException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Stmt {

/*************************************************************************/
Sort::Sort(Expr::XPath::XPathExprFamily  *pListExpr,
		 Program* pProgram,
		 bool bReverse):
		  ptrListExpr(pListExpr),
		  pProgram(pProgram),
		  bReverse(bReverse){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(ptrListExpr);
}
/*************************************************************************/
Sort::~Sort() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Sort::CallHelper::CallHelper(DM::DataObjectList& lstArray, const Program* pProgram, Exe::Context *pCtx):
	lstArray(lstArray),
	pCtx(pCtx){

	ptrContext = IAS_DFT_FACTORY<ProgramContext>::Create(pCtx->getDataFactory(), pProgram);

	const DM::ComplexType*  pComplexType  = ptrContext->getParameters()->getType()->asComplexType();
	const DM::PropertyList& lstProperties (pComplexType->getProperties());

	pPropertyLeft  = lstProperties.getProperty(0);
	pPropertyRight = lstProperties.getProperty(1);

	pParameters = ptrContext->getParameters();

}
/*************************************************************************/
bool Sort::CallHelper::cmp(DM::DataObject* pLeft, DM::DataObject* pRight){
	IAS_TRACER;

	pParameters->setDataObject(pPropertyLeft, pLeft);
	pParameters->setDataObject(pPropertyRight, pRight);

	ptrContext->execute(pCtx);

	return ptrContext->getResult()->toBoolean();
}
/*************************************************************************/
void Sort::CallHelper::swap(int iLeftIdx, int iRightIdx){

	if(iLeftIdx == iRightIdx)
		return;

	DM::DataObjectPtr ptrTmp0 = lstArray[iLeftIdx];
	DM::DataObjectPtr ptrTmp1 = lstArray[iRightIdx];

	lstArray.set(iLeftIdx,0);
	lstArray.set(iRightIdx,0);

	lstArray.set(iLeftIdx,ptrTmp1);
	lstArray.set(iRightIdx,ptrTmp0);
}
/*************************************************************************/
void Sort::CallHelper::sort(int iLeftIdx, int iRightIdx){

	IAS_TRACER;

	if(iLeftIdx < iRightIdx){
		int iIdx = partition(iLeftIdx, iRightIdx);
		sort(iLeftIdx, iIdx);
		sort(iIdx + 1, iRightIdx);
	}

}
/*************************************************************************/
int Sort::CallHelper::partition(int iLeftIdx, int iRightIdx){

	int iPivotIdx = (iLeftIdx + iRightIdx) / 2;
	DM::DataObject *pPivot = lstArray.at(iPivotIdx);

	swap(iPivotIdx, iRightIdx);

	int iCurrent = iLeftIdx;

	for(int iIdx = iLeftIdx; iIdx < iRightIdx ; iIdx++){

		if(cmp(lstArray.at(iIdx), pPivot)){
			swap(iIdx,iCurrent);
			iCurrent++;
		}
	};

	swap(iCurrent, iRightIdx);

	return iCurrent;
}
/*************************************************************************/
void Sort::CallHelper::sort(){
	IAS_TRACER;
	sort(0, lstArray.size() - 1);
}
/*************************************************************************/
void Sort::execute(Context *pCtx) const{
	IAS_TRACER;

	DM::DataObjectPtr dmContext;

	DM::DataObjectList& lstArray(ptrListExpr->getTargetObjectList(pCtx));

	CallHelper ch(lstArray, pProgram, pCtx);

	ch.sort();
}
/*************************************************************************/
}
}
}
}
}
