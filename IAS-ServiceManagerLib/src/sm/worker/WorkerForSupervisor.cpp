/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForSupervisor.cpp
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
#include "WorkerForSupervisor.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "StartStopHelper.h"
#include "sm/mon/Monitor.h"
#include "sm/mon/ServiceStatus.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
WorkerForSupervisor::WorkerForSupervisor(const Cfg::Config *pConfig, const Mon::Monitor* pMonitor) {
	IAS_TRACER;

	this->pConfig = pConfig;
	this->pMonitor = pMonitor;
	ptrStartStopHelper = IAS_DFT_FACTORY<StartStopHelper>::Create(pConfig);

}
/*************************************************************************/
WorkerForSupervisor::~WorkerForSupervisor() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void WorkerForSupervisor::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	const Mon::ServiceStatus* pServiceStatus = pMonitor->getServiceStatus(pService);

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount           = dmResourceGrp->getCount();

	int iRestartInterval = dmResourceGrp->isSetRestartInterval() ? dmResourceGrp->getRestartInterval() : 60;
	time_t tNow = time(0);

	for (int iIdx = 0; iIdx < iCount; iIdx++) {
		const Mon::ServiceStatus::InstanceStatus *pInstanceStatus = pServiceStatus->getInstanceStatus(iIdx);

		FailedServicesMap::iterator it = hmFailedServices.find(pService);

		if(pInstanceStatus->bIsStarted){

			if(!pInstanceStatus->bIsRunning)
			{
				if(it == hmFailedServices.end()) {
					ptrStartStopHelper->startInstance(pService,iIdx);
					hmFailedServices[pService] = tNow + (iRestartInterval / 2);
				} else if(tNow > it->second) {
					ptrStartStopHelper->startInstance(pService,iIdx);
					hmFailedServices[pService] = tNow + iRestartInterval;
				} else {
					IAS_LOG(LogLevel::INSTANCE.isInfo(), "Waiting  : "<<pService->getName()<<" "<< (hmFailedServices[pService] - tNow));
				}

			}else{

				if(it != hmFailedServices.end()){
					if(tNow > it->second) {
						hmFailedServices.erase(it);
					}
				}

			}/* IF: isRunning */

		}/* IF: isStarted */

	}/* while */
}
/*************************************************************************/

}
}
}
