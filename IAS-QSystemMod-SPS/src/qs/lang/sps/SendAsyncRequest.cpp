/*
 * File: IAS-QSystemMod-SPS/src/qs/lang/sps/SendAsyncRequest.cpp
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
#include "SendAsyncRequest.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <lang/interpreter/exe/Context.h>
#include <lang/model/dec/ResultDeclarationNode.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/io/Output.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/Context.h>

#include <qs/workers/proc/logic/sps/Helper.h>

using namespace ::IAS::Lang::Interpreter;
using namespace ::org::invenireaude::qsystem;
using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Lang {
namespace SPS {


/*************************************************************************/
SendAsyncRequest::SendAsyncRequest(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
}
/*************************************************************************/
SendAsyncRequest::~SendAsyncRequest() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SendAsyncRequest::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	const String strOutputName = pParameters->getString("name");
	workers::Ext::ContextPtr  dmCtx  = workers::DataFactory::GetInstance()->getContextType()->cast(pParameters->getDataObject("ctx"));

	DM::DataObjectPtr dmData(pParameters->getDataObject("data"));

	Workers::Proc::Logic::SPS::Helper::UpdateContext(dmCtx,pProcessCacheEntry->getProcessInstance()->getId(),
													pProcessCacheEntry->getProcessInstance()->getSeq()+1);

	pWorkContext->getIOManager()->getOutput(strOutputName)->send(dmCtx,dmData);

	pProcessCacheEntry->registerRequest();

}
/*************************************************************************/
Extern::Statement* SendAsyncRequest::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<SendAsyncRequest>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

