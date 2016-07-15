/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ModifyDate.cpp
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
#include "ModifyDate.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {

/*************************************************************************/
ModifyDate::ModifyDate(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
ModifyDate::~ModifyDate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ModifyDate::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	int iDeltaYears    = pParameters->getInteger("iDeltaYears");
	int iDeltaMonths  = pParameters->getInteger("iDeltaMonths");
	int iDeltaDays  = pParameters->getInteger("iDeltaDays");

	DateTime tsValue = pParameters->getDateTime("tTime");

	unsigned short iYear;
	unsigned short iMonth;
	unsigned short iDay;

	tsValue.getDate(iYear,iMonth,iDay);

	iYear+=iDeltaYears;
	iMonth+=iDeltaMonths;
	iDay+=iDeltaDays;

	tsValue.setDate(iYear,iMonth,iDay);

	pParameters->setDateTime(String(Model::Dec::ResultDeclarationNode::CStrResultVariable),
							 tsValue);

}
/*************************************************************************/
Statement* ModifyDate::Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	tzset();
	return IAS_DFT_FACTORY<ModifyDate>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
