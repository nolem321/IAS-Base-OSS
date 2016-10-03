/*
 * File: IAS-LangLib/src/lang/interpreter/exe/expr/ConstExprFamily.cpp
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
#include "ConstExprFamily.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "ConstIntegerExpr.h"
#include "ConstBooleanExpr.h"
#include "ConstStringExpr.h"
#include "ConstFloatExpr.h"
#include "ConstDateTimeExpr.h"
#include "ConstDateExpr.h"
#include "ConstTimeExpr.h"
#include "ConstNullExpr.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Exe {
namespace Expr {

/*************************************************************************/
Expr* ConstExprFamily::Create(const DM::Type* pType, const String& strValue){
	IAS_TRACER;

	IAS_DFT_FACTORY<ConstExprFamily>::PtrHolder ptrExpr;
	switch(pType->getTypeEnum()){

	case DM::Type::IntegerType:
		ptrExpr = IAS_DFT_FACTORY<ConstIntegerExpr>::Create(IAS::TypeTools::StringToInt(strValue));
		break;

	case DM::Type::TextType:
		ptrExpr = IAS_DFT_FACTORY<ConstStringExpr>::Create(strValue);
		break;

	case DM::Type::BooleanType:

		if(strValue.compare("TRUE") == 0)
			ptrExpr = IAS_DFT_FACTORY<ConstBooleanExpr>::Create(true);
		else if(strValue.compare("FALSE") == 0)
			ptrExpr = IAS_DFT_FACTORY<ConstBooleanExpr>::Create(false);
		else
			IAS_THROW(BadUsageException("TRUE or FALSE constants "));

		break;

	case DM::Type::FloatType:
		ptrExpr = IAS_DFT_FACTORY<ConstFloatExpr>::Create(IAS::TypeTools::StringToFloat(strValue));
		break;

//TODO (M) to jest cos dziwnego - czemu konwersji nie robi DM ?

	case DM::Type::DateType:
		ptrExpr = IAS_DFT_FACTORY<ConstDateTimeExpr>::Create(IAS::Date(strValue));
		break;

	case DM::Type::TimeType:
		ptrExpr = IAS_DFT_FACTORY<ConstDateTimeExpr>::Create(IAS::Time(strValue));
		break;

	case DM::Type::DateTimeType:
		ptrExpr = IAS_DFT_FACTORY<ConstDateTimeExpr>::Create(IAS::DateTime(strValue));
		break;

	case DM::Type::AnyType:
		ptrExpr = IAS_DFT_FACTORY<ConstNullExpr>::Create();
		break;

	default:
		IAS_THROW(InternalException("No factory for operator!"));
		break;
	}

	ptrExpr->setType(pType);
	return ptrExpr.pass();
}
/*************************************************************************/
}
}
}
}
}
