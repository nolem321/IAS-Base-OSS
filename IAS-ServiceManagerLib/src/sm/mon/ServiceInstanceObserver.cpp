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
#include "unistd.h"

namespace IAS {
namespace SM {
namespace Mon {

/*
 * This is workaround for close(), see the man page
 * Any record locks (see fcntl(2)) held on the
       file it was associated with, and owned by the process, are removed
       (regardless of the file descriptor that was used to obtain the lock).
 */
String           ServiceInstanceObserver::MyServiceName;
ProcessLockFile *ServiceInstanceObserver::MyProcessLockFile(0);
/*************************************************************************/
ServiceInstanceObserver::ServiceInstanceObserver(const Monitor *pMonitor,
												 ServiceStatus* pServiceStatus,
												 int iInstanceIdx):
   pMonitor(pMonitor),
   pServiceStatus(pServiceStatus),
   iInstanceIdx(iInstanceIdx){

	IAS_TRACER;

	strServiceName = pServiceStatus->getService()->getName() + TypeTools::IntToString(iInstanceIdx);

	if(MyServiceName.compare(strServiceName) == 0){
		IAS_CHECK_IF_NULL(MyProcessLockFile);
		ptrLockFile=MyProcessLockFile;
	}else{
		ptrLockFile=IAS_DFT_FACTORY<ProcessLockFile>::Create(
			pMonitor->getConfig()->getLckDir(),
			pServiceStatus->getService(), iInstanceIdx);
	}
}
/*************************************************************************/
ServiceInstanceObserver::~ServiceInstanceObserver() throw(){
	IAS_TRACER;

	if(ptrLockFile == MyProcessLockFile)
		ptrLockFile.pass();
}
/*************************************************************************/
void ServiceInstanceObserver::refresh(){
	IAS_TRACER;

	ServiceStatus::InstanceStatus* pInstanceStatus=pServiceStatus->getInstanceStatus(iInstanceIdx);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Observing: "<<pServiceStatus->getService()->getName()<<":"<<iInstanceIdx);

	ProcessLockFile::State      iState;
	ptrLockFile->getProcessPidAndState(pInstanceStatus->iPid, iState);
	pInstanceStatus->bIsStarted=iState==ProcessLockFile::PS_STARTED;


	if(pInstanceStatus->iPid == getpid()){
		pInstanceStatus->bIsRunning = true;
		MyProcessLockFile=ptrLockFile;
		MyServiceName=strServiceName;
	}else{
		pInstanceStatus->bIsRunning = ptrLockFile->isLocked();
	}


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"My PID: "<<getpid());

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Status: "<<pInstanceStatus->bIsStarted<<":"<<pInstanceStatus->bIsRunning<<":"<<pInstanceStatus->iPid);


}
/*************************************************************************/
}
}
}
