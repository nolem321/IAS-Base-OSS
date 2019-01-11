/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/GetHash.cpp
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
#include "GetHash.h"
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>
#include <stdlib.h>

namespace IAS {
namespace Lang {
namespace Interpreter {
namespace Extern {
namespace Std {
namespace Security {

/*************************************************************************/
GetHash::GetHash(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;

	if(lstParamaters.size())
		srand(TypeTools::StringToInt(*lstParamaters.begin()));
}
/*************************************************************************/
GetHash::~GetHash() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetHash::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);
	String strValue(pParameters->getString("value"));

	int iValue = hash(strValue) % (INT_MAX >> 1);

	pParameters->setInteger(String(Model::Dec::ResultDeclarationNode::CStrResultVariable),
							iValue);

}
/*************************************************************************/
Statement* GetHash::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetHash>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
}
