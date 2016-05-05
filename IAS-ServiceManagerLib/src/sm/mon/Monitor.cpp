/*
 * File: IAS-ServiceManagerLib/src/sm/mon/Monitor.cpp
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
#include "Monitor.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "ServiceStatus.h"
#include "ServiceInstanceObserver.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
Monitor::Monitor(const Cfg::Config* pConfig){
	IAS_TRACER;
	init(pConfig);
}
/*************************************************************************/
Monitor::~Monitor() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const ServiceStatus* Monitor::getServiceStatus(const Service* pService) const{
	IAS_TRACER;

	if(hmServiceStatus.count(pService) == 0){
		IAS_THROW(ItemNotFoundException("hmServiceStatus.count(pService) == 0"));
	}

	return hmServiceStatus.at(pService);
}
/*************************************************************************/
void Monitor::refresh(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Refresh.");

	for(IAS_DFT_FACTORY<ServiceInstanceObserver>::PtrHoldersCollection::iterator it=phcObservers.begin();
			it != phcObservers.end(); it++){
		(*it)->refresh();
	}
}
/*************************************************************************/
void Monitor::init(const Cfg::Config* pConfig){
	IAS_TRACER;

	this->pConfig=pConfig;

	const Ext::ServiceList& lstServices(pConfig->getServicesList());

		for(int iIdx=0; iIdx<lstServices.size(); iIdx++ ){
			const Service* pService = lstServices.at(iIdx);

			const ResourceGroup* pResourceGroup = pConfig->getMergedServiceResourceGrps(pService);

			int iCount = pResourceGroup->getCount();

			ServiceStatus* pServiceStatus = IAS_DFT_FACTORY<ServiceStatus>::Create(pService, iCount);
			hmServiceStatus[pService] = pServiceStatus;

			for(int iInstance=0; iInstance<iCount; iInstance++){
				phcObservers.addPointer(IAS_DFT_FACTORY<ServiceInstanceObserver>::Create(this,pServiceStatus, iInstance));
			}
		}

}
/*************************************************************************/
const Cfg::Config* Monitor::getConfig()const{
	IAS_TRACER;
	return pConfig;
}
/*************************************************************************/
}
}
}
