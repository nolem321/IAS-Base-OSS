/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForStop.cpp
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
#include "WorkerForStop.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "StartStopHelper.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
WorkerForStop::WorkerForStop() throw ():pConfig(0) {
	IAS_TRACER;
}

/*************************************************************************/
WorkerForStop::~WorkerForStop() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void WorkerForStop::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount = dmResourceGrp->getCount();


	for (int iIdx = 0; iIdx < iCount; iIdx++) {
		ptrStartStopHelper->stopInstance(pService, iIdx);
	}/* FOR: instances */
}
/*************************************************************************/
class StartStopHelperThreadProxy: public ::IAS::Runnable, public Thread {
public:
	virtual ~StartStopHelperThreadProxy(){};

	StartStopHelperThreadProxy(const StartStopHelper *pStartStopHelper, const Service* pService, int iIdx) :
		Thread(this),
		pStartStopHelper(pStartStopHelper), pService(pService), iIdx(iIdx) {
	};

	virtual void run() {
		pStartStopHelper->stopInstance(pService, iIdx);
	};

protected:
	const StartStopHelper *pStartStopHelper;
	const Service* pService;
	int iIdx;
};
/*************************************************************************/
class WorkerForStopAsync: public WorkerForStop {
public:

	virtual ~WorkerForStopAsync()throw(){

	for(IAS_DFT_FACTORY<Thread>::PtrHoldersCollection::iterator it=phcThreads.begin();
			it != phcThreads.end(); it++){
				(*it)->join();
			}
	};

	virtual void work(const ::org::invenireaude::sm::cfg::Service* pService);
protected:
	WorkerForStopAsync() throw () {};
	friend class ::IAS::Factory<WorkerForStopAsync>;

	IAS_DFT_FACTORY<Thread>::PtrHoldersCollection phcThreads;
};
/*************************************************************************/
void WorkerForStopAsync::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount = dmResourceGrp->getCount();
	for (int iIdx = 0; iIdx < iCount; iIdx++) {

		StartStopHelperThreadProxy *pProxy;
		pProxy=IAS_DFT_FACTORY<StartStopHelperThreadProxy>::Create(ptrStartStopHelper.getPointer(),pService,iIdx);
		phcThreads.addPointer(pProxy);
		pProxy->start();

	}

}
/*************************************************************************/
void WorkerForStop::init(const ::IAS::SM::Cfg::Config *pConfig) {
	IAS_TRACER;
	this->pConfig = pConfig;
	ptrStartStopHelper = IAS_DFT_FACTORY<StartStopHelper>::Create(pConfig);
}
/*************************************************************************/
WorkerForStop* WorkerForStop::Create(const ::IAS::SM::Cfg::Config *pConfig, bool bAsync) {
	IAS_TRACER;

	IAS_DFT_FACTORY<WorkerForStop>::PtrHolder ptrWorkerForStop;

	if (!bAsync) {
		ptrWorkerForStop = IAS_DFT_FACTORY<WorkerForStop>::Create();
	} else {
		ptrWorkerForStop = IAS_DFT_FACTORY<WorkerForStopAsync>::Create();
	}

	ptrWorkerForStop->init(pConfig);
	return ptrWorkerForStop.pass();
}
/*************************************************************************/

}
}
}
