/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/RelationFamily.cpp
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
#include "RelationFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "RelationBooleanExpr.h"
#include "RelationFloatExpr.h"
#include "RelationIntegerExpr.h"
#include "RelationStringExpr.h"
#include "RelationDateTimeExpr.h"
#include "RelationDateExpr.h"
#include "RelationTimeExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
RelationFamily::RelationFamily(Expr* pLeft, Expr* pRight):
	ptrLeft(pLeft),ptrRight(pRight){
	IAS_TRACER;
}

/*************************************************************************/
RelationFamily::~RelationFamily() throw(){
	IAS_TRACER;
}
/*************************************************************************/
BooleanExpr* RelationFamily::Create(const DM::DataFactory* pDataFactory,Expr* pLeft, Expr* pRight, TypeInfoProxy aTypeInfoProxy){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pLeft);
	IAS_CHECK_IF_NULL(pRight);

	DM::Type::Types iTypeId = pLeft->getType()->getTypeEnum();

	IAS_DFT_FACTORY<RelationFamily>::PtrHolder ptrExpr;

	switch(iTypeId){

		case DM::Type::TextType:
			ptrExpr = RelationStringExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::IntegerType:
			ptrExpr = RelationIntegerExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::BooleanType:
			ptrExpr = RelationBooleanExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::FloatType:
			ptrExpr=RelationFloatExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::DateTimeType:
			ptrExpr=RelationDateTimeExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::DateType:
			ptrExpr=RelationDateExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;

		case DM::Type::TimeType:
			ptrExpr=RelationTimeExpr::Create(pLeft,pRight,aTypeInfoProxy);
			break;


		default:
			IAS_THROW(InternalException("No factory for operator!"));
		break;
	}

	ptrExpr->setType(pDataFactory->getDefaultType(DM::Type::BooleanType));
	return ptrExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
