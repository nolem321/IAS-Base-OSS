/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/UnaryExprFamily.cpp
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
#include "UnaryExprFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "UnaryIntegerExpr.h"
#include "UnaryDataObjectExpr.h"
#include "UnaryBooleanExpr.h"
#include "UnaryFloatExpr.h"
#include "UnaryStringExpr.h"
#include "UnaryDateTimeExpr.h"
#include "UnaryDateExpr.h"
#include "UnaryTimeExpr.h"

#include <lang/exception/ScriptUsageException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
UnaryExprFamily::UnaryExprFamily(Expr* pExpr){
	IAS_TRACER;
	ptrExpr=pExpr;
}

/*************************************************************************/
UnaryExprFamily::~UnaryExprFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Expr* UnaryExprFamily::Create(Expr* pExpr, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pExpr);

	DM::Type::Types iTypeId = pExpr->getType()->getTypeEnum();

	IAS_DFT_FACTORY<UnaryExprFamily>::PtrHolder ptrResult;

	switch(iTypeId){

		case DM::Type::BooleanType:
			ptrResult = UnaryBooleanExpr::Create(pExpr,aTypeInfoProxy);
			break;

		case DM::Type::FloatType:
			ptrResult= UnaryFloatExpr::Create(pExpr,aTypeInfoProxy);
			break;

		case DM::Type::IntegerType:
			ptrResult = UnaryIntegerExpr::Create(pExpr,aTypeInfoProxy);
			break;

		case DM::Type::TextType:
			ptrResult = UnaryStringExpr::Create(pExpr,aTypeInfoProxy);
			break;

		case DM::Type::DateTimeType:
			ptrResult = UnaryDateTimeExpr::Create(pExpr,aTypeInfoProxy);
			break;
		case DM::Type::DateType:
			ptrResult = UnaryDateExpr::Create(pExpr,aTypeInfoProxy);
			break;
		case DM::Type::TimeType:
			ptrResult = UnaryTimeExpr::Create(pExpr,aTypeInfoProxy);
			break;

		case DM::Type::DataObjectType:
		case DM::Type::AnyType:
			ptrResult =  UnaryDataObjectExpr::Create(pExpr,aTypeInfoProxy);
			break;

		default:
			IAS_LOG(::IAS::Lang::LogLevel::INSTANCE.isError(),"typeId:["<<iTypeId<<"]:");
			IAS_THROW(ScriptUsageException(String("No operator factor for this type.") +  pExpr->getType()->getFullName()));

			break;
	}

	ptrResult->setType(pExpr->getType());
	return ptrResult.pass();
}
/*************************************************************************/
}
}
}
}
}

