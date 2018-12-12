/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/PartOfString.cpp
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
#include "PartOfString.h"
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
PartOfString::PartOfString(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
PartOfString::~PartOfString() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void PartOfString::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;
	DM::DataObject* pParameters = pCtx->getBlockVariables(0);
	const String strArgument = pParameters->getString("strArgument");
  const String strPattern  = pParameters->getString("strPattern");
  int   iFieldNo           = pParameters->getInteger("iFieldNo");

  size_t iIdx1 = 0;

  while(--iFieldNo && iIdx1 != String::npos) {

    iIdx1 = strArgument.find(strPattern.c_str(), iIdx1);

    if(iIdx1 != String::npos)
      iIdx1++;
  }

  if(iIdx1 == String::npos)
    return; // Empty string;

  size_t iIdx2 = strArgument.find(strPattern.c_str(), iIdx1);

  pParameters->setString(Model::Dec::ResultDeclarationNode::CStrResultVariable, strArgument.substr(iIdx1,
    iIdx2 != String::npos ? iIdx2 - iIdx1 : String::npos));

}
/*************************************************************************/
Statement* PartOfString::Create(const DM::Type* pType, const StringList& lstParamaters, const ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<PartOfString>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
