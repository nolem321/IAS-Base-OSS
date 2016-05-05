/*
 * File: IAS-ServiceManagerLib/src/sm/worker/exe/Handler.h
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
#ifndef _IAS_SM_Worker_Exe_Handler_H_
#define _IAS_SM_Worker_Exe_Handler_H_

#include <commonlib/commonlib.h>
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Worker {
namespace Exe {
class ExecutorFactory;
/*************************************************************************/
/** The Handler class.
 *
 */
class Handler {
public:

	virtual ~Handler() throw();

	::IAS::SYS::Proc::Executor *createExecutor(const ::org::invenireaude::sm::cfg::ResourceGroupExe* pExeSpec,
											   const ::org::invenireaude::sm::cfg::Command* pCommand)const;

protected:
	Handler();

	typedef HashMapStringToPointer<ExecutorFactory> ExecutorFactoriesMap;

	ExecutorFactoriesMap hmExecutorFactories;

	const ExecutorFactory* getFactory(const DM::Type* pType)const;

	friend class ::IAS::Factory<Handler>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_SM_Worker_Exe_Handler_H_ */
