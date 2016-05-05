/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ModifyTime.cpp
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
#include "ModifyTime.h"
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
ModifyTime::ModifyTime(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
ModifyTime::~ModifyTime() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ModifyTime::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	int iDeltaHours    = pParameters->getInteger("iDeltaHours");
	int iDeltaMinutes  = pParameters->getInteger("iDeltaMinutes");
	int iDeltaSeconds  = pParameters->getInteger("iDeltaSeconds");

	DateTime tsValue = pParameters->getDateTime("tTime");

	unsigned short iHour;
	unsigned short iMinute;
	unsigned short iSecond;
	unsigned int   iUSec=0;

	tsValue.getTime(iHour,iMinute,iSecond,iUSec);

	iHour+=iDeltaHours;
	iMinute+=iDeltaMinutes;
	iSecond+=iDeltaSeconds;

	tsValue.setTime(iHour,iMinute,iSecond);

	pParameters->setDateTime(String(Model::Dec::ResultDeclarationNode::CStrResultVariable),
							 tsValue);

}
/*************************************************************************/
Statement* ModifyTime::Create(const StringList& lstParamaters){
	IAS_TRACER;
	tzset();
	return IAS_DFT_FACTORY<ModifyTime>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}
}
