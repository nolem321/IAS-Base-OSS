/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForSupervisor.h
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
#ifndef _IAS_SM_Worker_WorkerForSupervisor_H_
#define _IAS_SM_Worker_WorkerForSupervisor_H_

#include "IWorker.h"
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Mon{
class Monitor;
}
namespace Cfg{
class Config;
}
namespace Worker {
class StartStopHelper;
namespace Exe {
class Handler;
}
/*************************************************************************/
/** The WorkerForSupervisor class.
 *
 */
class WorkerForSupervisor : public IWorker {
public:

	virtual ~WorkerForSupervisor() throw();

	virtual void work(const ::org::invenireaude::sm::cfg::Service* pService);

protected:
	WorkerForSupervisor(const ::IAS::SM::Cfg::Config *pConfig, const ::IAS::SM::Mon::Monitor* pMonitor);

	IAS_DFT_FACTORY<StartStopHelper>::PtrHolder ptrStartStopHelper;

	const ::IAS::SM::Cfg::Config *pConfig;
	const ::IAS::SM::Mon::Monitor* pMonitor;

	typedef std::map<const ::org::invenireaude::sm::cfg::Service*, unsigned int> FailedServicesMap;

	FailedServicesMap hmFailedServices;

	friend class ::IAS::Factory<WorkerForSupervisor>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_WorkerForSupervisor_H_ */
