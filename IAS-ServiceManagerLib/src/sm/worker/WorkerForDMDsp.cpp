/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForDMDsp.cpp
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
#include "WorkerForDMDsp.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "exe/Handler.h"
#include "Process.h"
#include "sm/mon/Monitor.h"
#include "sm/mon/ProcessLockFile.h"
#include "sm/mon/ServiceStatus.h"

using namespace ::org::invenireaude::sm;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
WorkerForDMDsp::WorkerForDMDsp(const Cfg::Config *pConfig,
								 const Mon::Monitor* pMonitor,
								 ::org::invenireaude::sm::api::Ext::ServiceStatusList& lstServiceStatusList):
					lstServiceStatusList(lstServiceStatusList){
	IAS_TRACER;

	this->pConfig  = pConfig;
	this->pMonitor = pMonitor;
	ptrExeHandler  = IAS_DFT_FACTORY<Exe::Handler>::Create();

}
/*************************************************************************/
WorkerForDMDsp::~WorkerForDMDsp() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void WorkerForDMDsp::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	api::Ext::ServiceStatusPtr dmServiceStatus;

	dmServiceStatus=api::DataFactory::GetInstance()->getServiceStatusType()->createServiceStatus();

	dmServiceStatus->setName(pService->getName());

	const Mon::ServiceStatus* pServiceStatus = pMonitor->getServiceStatus(pService);

	const cfg::ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount = dmResourceGrp->getCount();

	for (int iIdx = 0; iIdx < iCount; iIdx++) {

		const Mon::ServiceStatus::InstanceStatus *pInstanceStatus = pServiceStatus->getInstanceStatus(iIdx);

		api::Ext::InstanceStatusPtr dmInstanceStatus;

		if(pInstanceStatus->bIsRunning){
			dmServiceStatus->getStatusesList().add("Running");
		}else{

			if(pInstanceStatus->bIsStarted){
				dmServiceStatus->getStatusesList().add("Error");
			}else{
				dmServiceStatus->getStatusesList().add("Stopped");
			}
		}

	}

	lstServiceStatusList.add(dmServiceStatus);

}
/*************************************************************************/

}
}
}
