/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForTxtDsp.cpp
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
#include "WorkerForTxtDsp.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "exe/Handler.h"
#include "Process.h"
#include "sm/mon/Monitor.h"
#include "sm/mon/ProcessLockFile.h"
#include "sm/mon/ServiceStatus.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
WorkerForTxtDsp::WorkerForTxtDsp(const Cfg::Config *pConfig, const Mon::Monitor* pMonitor, bool bFailedOnly) {
	IAS_TRACER;

	this->pConfig = pConfig;
	this->pMonitor = pMonitor;
	this->bFailedOnly = bFailedOnly;
	ptrExeHandler = IAS_DFT_FACTORY<Exe::Handler>::Create();

}
/*************************************************************************/
WorkerForTxtDsp::~WorkerForTxtDsp() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void WorkerForTxtDsp::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	StringStream ssLine;

	const Mon::ServiceStatus* pServiceStatus = pMonitor->getServiceStatus(pService);

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount = dmResourceGrp->getCount();



	bool hasFailed = false;

	for (int iIdx = 0; iIdx < iCount; iIdx++) {

		const Mon::ServiceStatus::InstanceStatus *pInstanceStatus = pServiceStatus->getInstanceStatus(iIdx);
		ssLine << (pInstanceStatus->bIsRunning ? " X" : (pInstanceStatus->bIsStarted ? " !" : " ?"));
		hasFailed |=  !pInstanceStatus->bIsRunning && pInstanceStatus->bIsStarted;

	}

	if(bFailedOnly && !hasFailed)
		return;

	std::ostream& os = pConfig->getOutput();
	os.width(40);
	os << pService->getName();
	os.width(0);
	os << " : ";

	os << ssLine.str() << std::endl;

}
/*************************************************************************/

}
}
}
