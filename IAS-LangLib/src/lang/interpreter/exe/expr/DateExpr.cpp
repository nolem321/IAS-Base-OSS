/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DateExpr.cpp
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
#include "DateExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
DateExpr::DateExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DateExpr::~DateExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int DateExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDate(pCtx);
}
/*************************************************************************/
Float DateExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return (double)evaluateDate(pCtx);
}
/*************************************************************************/
bool  DateExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDate(pCtx);
}
/*************************************************************************/
String DateExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDate(pCtx).toString();
}
/*************************************************************************/
::IAS::DateTime DateExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDate(pCtx);
}
/*************************************************************************/
::IAS::Time  DateExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDate(pCtx);
}
/*************************************************************************/
void DateExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateDate(pCtx));
}
/*************************************************************************/
}
}
}
}
}
