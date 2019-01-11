/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StandardModuleProxy.cpp
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
#include "StandardModuleProxy.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "FormatDateTime.h"
#include "FormatDateTimeString.h"
#include "DateTimeToString.h"
#include "SubString2.h"
#include "SubString3.h"
#include "Find.h"
#include "Find3.h"
#include "PartOfString.h"
#include "Replace.h"
#include "ReplaceRegExp.h"
#include "GetTime.h"
#include "GetTimeFormated.h"
#include "GetLocalTimeFormated.h"
#include "GetYear.h"
#include "GetMonth.h"
#include "GetDay.h"
#include "ModifyDate.h"
#include "ModifyTime.h"
#include "GetTimeDiff.h"
#include "StrToLower.h"
#include "StrToUpper.h"
#include "StrLen.h"

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
StandardModuleProxy::StandardModuleProxy(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy::~StandardModuleProxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StandardModuleProxy::setupImpl(){

	IAS_TRACER;

  registerSymbol("FormatDateTime", &(FormatDateTime::Create));
  registerSymbol("FormatDateTimeString", &(FormatDateTimeString::Create));
	registerSymbol("DateTimeToString",&(DateTimeToString::Create));
	registerSymbol("SubString2",&(SubString2::Create));
	registerSymbol("SubString3",&(SubString3::Create));
	registerSymbol("Find",&(Find::Create));
  registerSymbol("Find3",&(Find3::Create));
  registerSymbol("PartOfString",&(PartOfString::Create));
	registerSymbol("Replace",&(Replace::Create));
	registerSymbol("ReplaceRegExp",&(ReplaceRegExp::Create));
	registerSymbol("GetTime",&(GetTime::Create));
	registerSymbol("GetTimeFormated",&(GetTimeFormated::Create));
	registerSymbol("GetLocalTimeFormated",&(GetLocalTimeFormated::Create));
	registerSymbol("GetYear",&(GetYear::Create));
	registerSymbol("GetMonth",&(GetMonth::Create));
	registerSymbol("GetDay",&(GetDay::Create));
	registerSymbol("ModifyTime",&(ModifyTime::Create));
	registerSymbol("ModifyDate",&(ModifyDate::Create));
	registerSymbol("GetTimeDiff",&(GetTimeDiff::Create));
	registerSymbol("StrToLower",&(StrToLower::Create));
	registerSymbol("StrToUpper",&(StrToUpper::Create));
	registerSymbol("StrLen",&(StrLen::Create));

}
/*************************************************************************/
void StandardModuleProxy::cleanUpImpl(){
	IAS_TRACER;
}
/*************************************************************************/
StandardModuleProxy* StandardModuleProxy::Create(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<StandardModuleProxy>::Create();
}
/*************************************************************************/
}
}
}
}
}
/*************************************************************************/
void* ias_lang_std_proxy(){
	IAS_TRACER;
	return ::IAS::Lang::Interpreter::Extern::Std::StandardModuleProxy::Create();
}
/*************************************************************************/
