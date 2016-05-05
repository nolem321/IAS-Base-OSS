/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DateTimeExpr.cpp
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
#include "DateTimeExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
DateTimeExpr::DateTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
DateTimeExpr::~DateTimeExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int DateTimeExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDateTime(pCtx);
}
/*************************************************************************/
Float DateTimeExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return (double)evaluateDateTime(pCtx);
}
/*************************************************************************/
bool  DateTimeExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return (long)evaluateDateTime(pCtx);
}
/*************************************************************************/
String DateTimeExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDateTime(pCtx).toString();
}
/*************************************************************************/
::IAS::Date  DateTimeExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDateTime(pCtx);
}
/*************************************************************************/
::IAS::Time  DateTimeExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	return evaluateDateTime(pCtx);
}
/*************************************************************************/
void DateTimeExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateDateTime(pCtx));
}
/*************************************************************************/
}
}
}
}
}
