/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/DataObjectExpr.cpp
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
#include "DataObjectExpr.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Context.h"
#include "../exception/NullObjectReferenceException.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
DataObjectExpr::DataObjectExpr() throw(){
	IAS_TRACER;
}

/*************************************************************************/
DataObjectExpr::~DataObjectExpr() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String DataObjectExpr::evaluateString(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toString();
}
/*************************************************************************/
int  DataObjectExpr::evaluateInt(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toInteger();
}
/*************************************************************************/
Float DataObjectExpr::evaluateFloat(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toFloat();
}
/*************************************************************************/
bool  DataObjectExpr::evaluateBoolean(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toBoolean();
}
/*************************************************************************/
::IAS::DateTime  DataObjectExpr::evaluateDateTime(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toDateTime();
}
/*************************************************************************/
::IAS::Date  DataObjectExpr::evaluateDate(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toDate();
}
/*************************************************************************/
::IAS::Time  DataObjectExpr::evaluateTime(Context *pCtx) const{
	IAS_TRACER;
	DM::DataObjectPtr ptrResult;
	evaluate(pCtx,ptrResult);

	if(!ptrResult)
		IAS_THROW(NullObjectReferenceException("Null expresion value."));

	return ptrResult->toTime();
}
/*************************************************************************/
}
}
}
}
}
