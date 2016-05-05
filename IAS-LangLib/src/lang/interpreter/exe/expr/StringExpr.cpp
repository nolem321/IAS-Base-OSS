/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/StringExpr.cpp
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
#include "StringExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
StringExpr::StringExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
StringExpr::~StringExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
int StringExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::StringToInt(evaluateString(pCtx));
}
/*************************************************************************/
Float StringExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::StringToFloat(evaluateString(pCtx));
}
/*************************************************************************/
bool  StringExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::StringToBoolean(evaluateString(pCtx));
}
/*************************************************************************/
::IAS::DateTime  StringExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	return DateTime(evaluateString(pCtx));
}
/*************************************************************************/
::IAS::Date  StringExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	return Date(evaluateString(pCtx));
}
/*************************************************************************/
::IAS::Time  StringExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	return Time(evaluateString(pCtx));
}
/*************************************************************************/
void StringExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateString(pCtx));
}
/*************************************************************************/
}
}
}
}
}
