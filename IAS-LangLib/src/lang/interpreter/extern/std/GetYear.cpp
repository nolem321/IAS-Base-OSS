/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/GetYear.cpp
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
#include "GetYear.h"
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
GetYear::GetYear(const StringList& lstParamaters){
	IAS_TRACER;
}
/*************************************************************************/
GetYear::~GetYear() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetYear::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	Date aDate(pParameters->getDate("date"));

	unsigned short iYear;
	unsigned short iMonth;
	unsigned short iDay;

	aDate.getDate(iYear,iMonth,iDay);

	pParameters->setInteger(Model::Dec::ResultDeclarationNode::CStrResultVariable,iYear);

}
/*************************************************************************/
Statement* GetYear::Create(const StringList& lstParamaters){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetYear>::Create(lstParamaters);
}
/*************************************************************************/
}
}
}
}
}
