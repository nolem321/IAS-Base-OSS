/*
 * File: IAS-LangMod-SysMon/src/lang/mod/monitor/tools/GetHostName.cpp
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
#include "GetHostName.h"

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <unistd.h>

using namespace ::IAS::Lang::Interpreter;

namespace IAS {
namespace Lang {
namespace MOD {
namespace Monitor {
namespace Tools {

/*************************************************************************/
GetHostName::GetHostName(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
GetHostName::~GetHostName() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetHostName::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	char sBuffer[1024];

	if(gethostname(sBuffer,1024) != 0)
		IAS_THROW(SystemException("gethostname"));

	String strHostName(sBuffer);

	pParameters->setString(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
					 strHostName);


}
/*************************************************************************/
Extern::Statement* GetHostName::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetHostName>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}
}
