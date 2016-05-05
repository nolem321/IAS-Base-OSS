/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/TimeExpr.cpp
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
#include "TimeExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
TimeExpr::TimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
TimeExpr::~TimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int TimeExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateTime(pCtx);
}
/*************************************************************************/
Float TimeExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return (double)evaluateTime(pCtx);
}
/*************************************************************************/
bool  TimeExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateTime(pCtx);
}
/*************************************************************************/
String TimeExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return evaluateTime(pCtx).toString();
}
/*************************************************************************/
::IAS::DateTime TimeExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	return evaluateTime(pCtx);
}
/*************************************************************************/
::IAS::Date  TimeExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	return evaluateTime(pCtx);
}
/*************************************************************************/
void TimeExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateTime(pCtx));
}
/*************************************************************************/
}
}
}
}
}
