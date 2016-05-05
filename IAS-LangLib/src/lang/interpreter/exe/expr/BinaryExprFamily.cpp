/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/BinaryExprFamily.cpp
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
#include "BinaryExprFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "BinaryBooleanExpr.h"
#include "BinaryFloatExpr.h"
#include "BinaryIntegerExpr.h"
#include "BinaryStringExpr.h"
#include "BinaryDateTimeExpr.h"
#include "BinaryDateExpr.h"
#include "BinaryTimeExpr.h"

#include <lang/exception/ScriptUsageException.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
BinaryExprFamily::BinaryExprFamily(Expr* pLeft, Expr* pRight){

	IAS_TRACER;

	ptrLeft=pLeft;
	ptrRight=pRight;

	setType(pLeft->getType());
}
/*************************************************************************/
BinaryExprFamily::~BinaryExprFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Expr* BinaryExprFamily::Create(Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pLeft);
	IAS_CHECK_IF_NULL(pRight);

	DM::Type::Types iTypeId = pLeft->getType()->getTypeEnum();

	switch(iTypeId){

		case DM::Type::TextType:     return BinaryStringExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::IntegerType:  return BinaryIntegerExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::BooleanType:  return BinaryBooleanExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::FloatType:    return BinaryFloatExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::DateTimeType:
			return BinaryDateTimeExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::DateType:
			return BinaryDateExpr::Create(pLeft,pRight,aTypeInfoProxy);
		case DM::Type::TimeType:
			return BinaryTimeExpr::Create(pLeft,pRight,aTypeInfoProxy);

	}

	IAS_THROW(ScriptUsageException(String("No factory for binary operator for ")
			+pLeft->getType()->getURI()+"#"+pLeft->getType()->getName()));
}
/*************************************************************************/
}
}
}
}
}
