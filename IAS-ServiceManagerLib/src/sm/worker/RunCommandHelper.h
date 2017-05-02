/*
 * File: IAS-ServiceManagerLib/src/sm/worker/RunCommandHelper.h
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
#ifndef _IAS_SM_Worker_RunCommandHelper_H_
#define _IAS_SM_Worker_RunCommandHelper_H_

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
/** The RunCommandHelper class.
 *
 */
class RunCommandHelper  {
public:

	virtual ~RunCommandHelper() throw();

    void run(const String& strServiceName);

protected:
	RunCommandHelper(const ::IAS::SM::Cfg::Config *pConfig, bool bSuppressDebug);

	const ::IAS::SM::Cfg::Config *pConfig;
	IAS_DFT_FACTORY<Exe::Handler>::PtrHolder ptrExeHandler;
	bool bSuppressDebug;
	friend class ::IAS::Factory<RunCommandHelper>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_RunCommandHelper_H_ */
