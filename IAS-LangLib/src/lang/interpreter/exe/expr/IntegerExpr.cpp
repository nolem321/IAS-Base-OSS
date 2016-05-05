/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/IntegerExpr.cpp
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
#include "IntegerExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
IntegerExpr::IntegerExpr() throw(){
	IAS_TRACER;
}

/*************************************************************************/
IntegerExpr::~IntegerExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String IntegerExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::IntToString(evaluateInt(pCtx));
}
/*************************************************************************/
Float IntegerExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return evaluateInt(pCtx);
}
/*************************************************************************/
bool  IntegerExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	return evaluateInt(pCtx) != 0;
}
/*************************************************************************/
::IAS::DateTime IntegerExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	DateTime tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Date IntegerExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	Date tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
::IAS::Time IntegerExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	time_t tmpValue=evaluateInt(pCtx);
	Time tsValue;
	tsValue.fromPosixTime(tmpValue);
	return tsValue;
}
/*************************************************************************/
void IntegerExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{

	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateString(pCtx));

}
/*************************************************************************/
}
}
}
}
}
