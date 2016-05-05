/*
 * File: IAS-ServiceManagerLib/src/sm/api/ActionDispatcher.cpp
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
#include "ActionDispatcher.h"

#include <org/invenireaude/sm/api/DataFactory.h>
#include <org/invenireaude/sm/api/ServiceStatusCall.h>
#include <org/invenireaude/sm/api/ServiceStatusRequest.h>
#include <org/invenireaude/sm/api/ServiceStatusResponse.h>
#include <org/invenireaude/sm/api/ServiceStatus.h>

#include <org/invenireaude/sm/api/ServiceConfigCall.h>
#include <org/invenireaude/sm/api/ServiceConfigRequest.h>
#include <org/invenireaude/sm/api/ServiceConfigResponse.h>

#include <org/invenireaude/sm/api/ServiceAction.h>
#include <org/invenireaude/sm/api/ServiceActionCall.h>
#include <org/invenireaude/sm/api/ServiceActionRequest.h>
#include <org/invenireaude/sm/api/ServiceActionResponse.h>


#include <org/invenireaude/sm/cfg/ServiceConfig.h>
#include <org/invenireaude/sm/cfg/DeploymentConfig.h>

#include "ServiceManager.h"
#include <sm/cfg/Config.h>

using namespace org::invenireaude::sm;

namespace IAS {
namespace SM {
namespace API {

/*************************************************************************/
ActionDispatcher::ActionDispatcher(ServiceManager *pServiceManager):
	pServiceManager(pServiceManager){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pServiceManager);

	hmCallback[api::DataFactory::GetInstance()->getServiceStatusCallType()]=
			&ActionDispatcher::serviceStatusCall;

	hmCallback[api::DataFactory::GetInstance()->getServiceConfigCallType()]=
				&ActionDispatcher::serviceConfigCall;

	hmCallback[api::DataFactory::GetInstance()->getServiceActionCallType()]=
				&ActionDispatcher::serviceActionCall;

}

/*************************************************************************/
ActionDispatcher::~ActionDispatcher() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ActionDispatcher::serviceCall(api::ServiceCall* pServiceCall){
	IAS_TRACER;

	const DM::Type* pType=pServiceCall->getType();

	CallbacksMap::const_iterator it=hmCallback.find(pType);

		if(it == hmCallback.end()){
			IAS_THROW(ItemNotFoundException(String("ActionDispatcher for: ")+pType->getName()));
		}

	 (this->*(it->second))(pServiceCall);
}
/*************************************************************************/
void ActionDispatcher::serviceStatusCall(api::ServiceCall* pServiceCall){
	IAS_TRACER;

	api::ServiceStatusCall* pServiceStatusCall(api::DataFactory::GetInstance()->getServiceStatusCallType()->cast(pServiceCall));

	pServiceStatusCall->createResponse();


	if(!pServiceStatusCall->isSetRequest())
		pServiceStatusCall->createRequest();

	if(!pServiceStatusCall->getRequest()->isSetSelector())
		pServiceStatusCall->getRequest()->createSelector();

	try{
		pServiceManager->prepareServicesStatus(pServiceStatusCall->getRequest()->getSelector()->getPairsList(),
											   pServiceStatusCall->getResponse()->getServicesList());
	}catch(ItemNotFoundException& e){

	}
}
/*************************************************************************/
void ActionDispatcher::serviceConfigCall(api::ServiceCall* pServiceCall){
	IAS_TRACER;

	api::ServiceConfigCall* pServiceConfigCall(api::DataFactory::GetInstance()->getServiceConfigCallType()->cast(pServiceCall));

	pServiceConfigCall->createResponse();

	cfg::Ext::ServiceConfigPtr    ptrServiceConfig;
	cfg::Ext::DeploymentConfigPtr ptrDeploymentConfig;

	pServiceManager->getConfig()->copyServiceConfig(ptrServiceConfig);
	pServiceManager->getConfig()->copyDeploymentConfig(ptrDeploymentConfig);

	pServiceConfigCall->getResponse()->setService(ptrServiceConfig);
	pServiceConfigCall->getResponse()->setDeployment(ptrDeploymentConfig);
}
/*************************************************************************/
void ActionDispatcher::serviceActionCall(api::ServiceCall* pServiceCall){
	IAS_TRACER;

	api::ServiceActionCall* pServiceActionCall(api::DataFactory::GetInstance()->getServiceActionCallType()->cast(pServiceCall));

	pServiceActionCall->createResponse();

	const api::Ext::ServiceActionList& lstActions(pServiceActionCall->getRequest()->getActionsList());

	for(int iIdx=0; iIdx<lstActions.size(); iIdx++){
		const api::ServiceAction* pAction=lstActions.at(iIdx);

		Cfg::GrpAttrPairList lstGrpAttrPairTmp;
		pServiceManager->fillGrpAttrPairList(pAction->getSelector()->getPairsList(),lstGrpAttrPairTmp);

		IAS_LOG(LogLevel::INSTANCE.isError(), "list size1="<<pAction->getSelector()->getPairsList().size());
		IAS_LOG(LogLevel::INSTANCE.isError(), "list size2="<<lstGrpAttrPairTmp.size());


		String strAction(pAction->getAction());

		if(strAction.compare("start")==0){
			pServiceManager->startServices(lstGrpAttrPairTmp);
		}else if(strAction.compare("stop")==0){
			//TODO in background or run as queue service !
			pServiceManager->stopServices(lstGrpAttrPairTmp,true);
		}else{
			IAS_THROW(ItemNotFoundException(strAction+" - unknown action name."));
		}

	}
}
/*************************************************************************/
}
}
}
