/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ServiceInstanceObserver.cpp
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
#include "ServiceInstanceObserver.h"

#include <commonlib/commonlib.h>

#include "ProcessLockFile.h"
#include "ServiceStatus.h"
#include "Monitor.h"
#include <sm/cfg/Config.h>

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
ServiceInstanceObserver::ServiceInstanceObserver(const Monitor *pMonitor,
												 ServiceStatus* pServiceStatus,
												 int iInstanceIdx):
   pMonitor(pMonitor),
   pServiceStatus(pServiceStatus),
   iInstanceIdx(iInstanceIdx){

	IAS_TRACER;

	ptrLockFile=IAS_DFT_FACTORY<ProcessLockFile>::Create(
			pMonitor->getConfig()->getLckDir(),
			pServiceStatus->getService(), iInstanceIdx);
}
/*************************************************************************/
ServiceInstanceObserver::~ServiceInstanceObserver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ServiceInstanceObserver::refresh(){
	IAS_TRACER;

	ServiceStatus::InstanceStatus* pInstanceStatus=pServiceStatus->getInstanceStatus(iInstanceIdx);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Observing: "<<pServiceStatus->getService()->getName()<<":"<<iInstanceIdx);

	pInstanceStatus->bIsRunning = ptrLockFile->isLocked();
	ProcessLockFile::State      iState;
	ptrLockFile->getProcessPidAndState(pInstanceStatus->iPid, iState);
	pInstanceStatus->bIsStarted=iState==ProcessLockFile::PS_STARTED;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Status: "<<pInstanceStatus->bIsStarted<<":"<<pInstanceStatus->bIsRunning<<":"<<pInstanceStatus->iPid);


}
/*************************************************************************/
}
}
}
