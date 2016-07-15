/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/StrToUpper.cpp
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
#include "StrToUpper.h"
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
StrToUpper::StrToUpper(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
StrToUpper::~StrToUpper() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StrToUpper::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);
	const String strArgument = pParameters->getString("strArgument");
	pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable, MiscTools::StrToUpper(strArgument));
}
/*************************************************************************/
Statement* StrToUpper::Create(const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<StrToUpper>::Create(lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
