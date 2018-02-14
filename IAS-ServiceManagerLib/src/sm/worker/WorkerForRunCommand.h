/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForRunCommand.h
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
#ifndef _IAS_SM_Worker_WorkerForRunCommand_H_
#define _IAS_SM_Worker_WorkerForRunCommand_H_

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
/** The WorkerForRunCommand class.
 *
 */
//class WorkerForRunCommand : public IWorker {
//public:
//
//	virtual ~WorkerForRunCommand() throw();
//
//    void run();
//
//protected:
//	WorkerForRunCommand(const ::org::invenireaude::sm::cfg::Service* pService);
//
//	const ::org::invenireaude::sm::cfg::Service* pService;
//
//	friend class ::IAS::Factory<WorkerForRunCommand>;
//};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_WorkerForRunCommand_H_ */
