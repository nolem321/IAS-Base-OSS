/*
 * File: IAS-QSystemLib/src/qs/lang/msgs/GetNumMessages.cpp
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
#include "GetNumMessages.h"
#include <qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>
#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/io/Controller.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Lang {
namespace Msgs {

/*************************************************************************/
GetNumMessages::GetNumMessages(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
GetNumMessages::~GetNumMessages() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void GetNumMessages::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strControllerName = pParameters->getString("name");

	pParameters->setInteger(String(IAS::Lang::Model::Dec::ResultDeclarationNode::CStrResultVariable),
			pWorkContext->getIOManager()->getController(strControllerName)->getNumMessages());

}
/*************************************************************************/
Extern::Statement* GetNumMessages::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<GetNumMessages>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

