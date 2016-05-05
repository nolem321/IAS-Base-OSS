/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForDMDsp.h
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
#ifndef _IAS_SM_Worker_WorkerForDMDsp_H_
#define _IAS_SM_Worker_WorkerForDMDsp_H_

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
namespace Exe {
class Handler;
}
/*************************************************************************/
/** The WorkerForDMDsp class.
 *
 */
class WorkerForDMDsp : public IWorker {
public:

	virtual ~WorkerForDMDsp() throw();

	virtual void work(const ::org::invenireaude::sm::cfg::Service* pService);

protected:
	WorkerForDMDsp(const ::IAS::SM::Cfg::Config *pConfig,
			        const ::IAS::SM::Mon::Monitor* pMonitor,
			        ::org::invenireaude::sm::api::Ext::ServiceStatusList& lstServiceStatusList);


private:

	::org::invenireaude::sm::api::Ext::ServiceStatusList& lstServiceStatusList;

	IAS_DFT_FACTORY<Exe::Handler>::PtrHolder ptrExeHandler;

	const ::IAS::SM::Cfg::Config *pConfig;
	const ::IAS::SM::Mon::Monitor* pMonitor;

	friend class ::IAS::Factory<WorkerForDMDsp>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_WorkerForDMDsp_H_ */
