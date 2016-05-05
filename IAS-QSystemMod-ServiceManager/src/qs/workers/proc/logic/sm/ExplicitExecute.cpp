/*
 * File: IAS-QSystemMod-ServiceManager/src/qs/workers/proc/logic/sm/ExplicitExecute.cpp
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
#include <errno.h>

#include "ExplicitExecute.h"
#include <qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

#include <org/invenireaude/sm/api/DataFactory.h>
#include <org/invenireaude/sm/api/ServiceCall.h>

#include <sm/api/ActionDispatcher.h>
#include <sm/api/ServiceManager.h>

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;
using namespace ::org::invenireaude::sm;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SM{

/*************************************************************************/
ExplicitExecute::ExplicitExecute(
		const ::org::invenireaude::qsystem::workers::logic::External* dmParameters,
		WCM::WorkContextManager* pWorkContextManager) :
		LogicBase(dmParameters, pWorkContextManager){
	IAS_TRACER;

	ptrServiceManager=IAS_DFT_FACTORY< ::IAS::SM::API::ServiceManager >::Create();
	ptrActionDispatcher=IAS_DFT_FACTORY< ::IAS::SM::API::ActionDispatcher >::Create< ::IAS::SM::API::ServiceManager* >(ptrServiceManager);
}
/*************************************************************************/
ExplicitExecute::~ExplicitExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExplicitExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		      DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==ExplicitExecute starts.");

	api::ServiceCall *pServiceCall = api::DataFactory::GetInstance()->getServiceCallType()->cast(dmData);

	ptrActionDispatcher->serviceCall(pServiceCall);
	pWorkContextManager->getIOManager()->getDefaultOutput()->send(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==ExplicitExecute ends.");
}
/*************************************************************************/
void ExplicitExecute::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							 API::Message* pMessage){

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute starts.");
	IAS_THROW(BadUsageException("computeRaw in the ServiceManager Driver"))
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute ends.");

}
/*************************************************************************/
}
}
}
}
}
}

/*************************************************************************/
extern "C"{
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_logic_sm(::org::invenireaude::qsystem::workers::logic::External*    dmParameters,
											             ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){

	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::SM::ExplicitExecute>::
			Create(dmParameters,pWorkContextManager);
  }

}
