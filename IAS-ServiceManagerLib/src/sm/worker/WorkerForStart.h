/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForStart.h
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
#ifndef _IAS_SM_Worker_WorkerForStart_H_
#define _IAS_SM_Worker_WorkerForStart_H_

#include "IWorker.h"
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Cfg{
class Config;
}
namespace Worker {
class StartStopHelper;
namespace Exe {
class Handler;
}
/*************************************************************************/
/** The WorkerForStart class.
 *
 */
class WorkerForStart : public IWorker {
public:

	virtual ~WorkerForStart() throw();

	virtual void work(const ::org::invenireaude::sm::cfg::Service* pService);

protected:
	WorkerForStart(const ::IAS::SM::Cfg::Config *pConfig);

	IAS_DFT_FACTORY<StartStopHelper>::PtrHolder ptrStartStopHelper;

	const ::IAS::SM::Cfg::Config *pConfig;

	friend class ::IAS::Factory<WorkerForStart>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_WorkerForStart_H_ */
