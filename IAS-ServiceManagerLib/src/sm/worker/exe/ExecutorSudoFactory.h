/*
 * File: IAS-ServiceManagerLib/src/sm/worker/exe/ExecutorSudoFactory.h
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
#ifndef _IAS_SM_Worker_Exe_ExecutorSudoFactory_H_
#define _IAS_SM_Worker_Exe_ExecutorSudoFactory_H_

#include "ExecutorFactory.h"

namespace IAS {
namespace SM {
namespace Worker {
namespace Exe {

/*************************************************************************/
/** The ExecutorSudoFactory class.
 *
 */
class ExecutorSudoFactory : public ExecutorFactory {
public:

	virtual ~ExecutorSudoFactory() throw();

	virtual ::IAS::SYS::Proc::Executor * create(const ::org::invenireaude::sm::cfg::ResourceGroupExe* pExeSpec,
												const ::org::invenireaude::sm::cfg::Command* pCommand)const;

protected:
	ExecutorSudoFactory();

	friend class ::IAS::Factory<ExecutorSudoFactory>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_SM_Worker_Exe_ExecutorSudoFactory_H_ */
