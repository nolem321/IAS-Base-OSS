/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BooleanExpr.cpp
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
#include "BooleanExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
BooleanExpr::BooleanExpr(){
	IAS_TRACER;
}
/*************************************************************************/
BooleanExpr::~BooleanExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String BooleanExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	return TypeTools::BoolToString(evaluateBoolean(pCtx));
}
/*************************************************************************/
Float BooleanExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	return evaluateBoolean(pCtx);
}
/*************************************************************************/
int  BooleanExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	return evaluateBoolean(pCtx);
}
/*************************************************************************/
::IAS::DateTime BooleanExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	IAS::DateTime tsResult;
	tsResult.setTime(0,0,evaluateBoolean(pCtx));
	return tsResult;
}
/*************************************************************************/
::IAS::Date BooleanExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	IAS::Date tsResult;
	tsResult.setTime(0,0,evaluateBoolean(pCtx));
	return tsResult;
}
/*************************************************************************/
::IAS::Time BooleanExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	IAS::Time tsResult;
	tsResult.setTime(0,0,evaluateBoolean(pCtx));
	return tsResult;
}
/*************************************************************************/
void BooleanExpr::evaluate(Context *pCtx, DM::DataObjectPtr& refResult) const{
	IAS_TRACER;
	const DM::DataFactory *pDataFactory=pCtx->getDataFactory();

	refResult = getType()->createDataObject(evaluateString(pCtx));
}
/*************************************************************************/
}
}
}
}
}
