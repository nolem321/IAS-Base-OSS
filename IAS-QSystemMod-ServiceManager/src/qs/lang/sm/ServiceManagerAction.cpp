/*
 * File: IAS-LangLib/src/lang/interpreter/extern/std/ti/ServiceManagerAction.cpp
 *
 * Copyright (C) 2015, Albert Krzymowski
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/SMCENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ServiceManagerAction.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <lang/model/dec/ResultDeclarationNode.h>
#include <lang/interpreter/exe/exception/InterpreterProgramException.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Exception.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <org/invenireaude/sm/api/DataFactory.h>
#include <org/invenireaude/sm/api/ServiceCall.h>

#include <sm/api/ActionDispatcher.h>
#include <sm/api/ServiceManager.h>

using namespace org::invenireaude::qsystem;
using namespace org::invenireaude::sm;
using namespace IAS::Lang;
using namespace IAS::Lang::Interpreter;

namespace IAS {
namespace QS {
namespace Lang {
namespace SM {


/*************************************************************************/
ServiceManagerAction::ServiceManagerAction(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;

  ptrServiceManager=IAS_DFT_FACTORY< ::IAS::SM::API::ServiceManager >::Create();
  ptrActionDispatcher=IAS_DFT_FACTORY< ::IAS::SM::API::ActionDispatcher >::Create< ::IAS::SM::API::ServiceManager* >(ptrServiceManager);
}
/*************************************************************************/
ServiceManagerAction::~ServiceManagerAction() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ServiceManagerAction::executeExternal(Exe::Context *pCtx) const{
	IAS_TRACER;

	DM::DataObject* pParameters = pCtx->getBlockVariables(0);

	try{

		DM::DataObjectPtr dmData(pParameters->getDataObject("data"));

    api::ServiceCall *pServiceCall = api::DataFactory::GetInstance()->getServiceCallType()->cast(dmData);

	  ptrActionDispatcher->serviceCall(pServiceCall);

		pParameters->setDataObject(Model::Dec::ResultDeclarationNode::CStrResultVariable,dmData);


	}catch(Exception& e){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),e.getName()<<":"<<e.getInfo());

		workers::Ext::ExceptionPtr dmException=workers::DataFactory::GetInstance()->createException();
		dmException->setName(e.getName());
		dmException->setInfo(e.toString());

		IAS_THROW(::IAS::Lang::Interpreter::Exe::InterpreterProgramException(dmException));


	}

}
/*************************************************************************/
Extern::Statement* ServiceManagerAction::Create(const DM::Type* pType, const StringList& lstParamaters, const ::IAS::Lang::Interpreter::Extern::ModuleProxy* pModuleProxy){
	IAS_TRACER;
	return IAS_DFT_FACTORY<ServiceManagerAction>::Create(pType, lstParamaters, pModuleProxy);
}
/*************************************************************************/
}
}
}
}

