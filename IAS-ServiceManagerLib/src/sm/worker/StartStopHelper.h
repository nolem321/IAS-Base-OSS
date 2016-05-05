/*
 * File: IAS-ServiceManagerLib/src/sm/worker/StartStopHelper.h
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
#ifndef _IAS_SM_Worker_StartStopHelper_H_
#define _IAS_SM_Worker_StartStopHelper_H_

#include "IWorker.h"
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Cfg{
class Config;
}
namespace Worker {
namespace Exe {
class Handler;
}
/*************************************************************************/
/** The StartStopHelper class.
 *
 */
class StartStopHelper {
public:

	virtual ~StartStopHelper() throw();

	virtual void startInstance(const ::org::invenireaude::sm::cfg::Service* pService, int iIdx)const;
	virtual void stopInstance(const ::org::invenireaude::sm::cfg::Service* pService, int iIdx, bool bKillGroups = false)const;


protected:
	StartStopHelper(const ::IAS::SM::Cfg::Config *pConfig);

	void kill(const ::org::invenireaude::sm::cfg::ResourceGroup* dmResourceGrp, int iSignal, int iPid, const String& strInfo) const;

private:

	IAS_DFT_FACTORY<Exe::Handler>::PtrHolder ptrExeHandler;
	const ::IAS::SM::Cfg::Config *pConfig;

	static Mutex mutexUserMsgs;
	friend class ::IAS::Factory<StartStopHelper>;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Worker_StartStopHelper_H_ */
