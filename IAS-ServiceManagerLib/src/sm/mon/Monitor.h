/*
 * File: IAS-ServiceManagerLib/src/sm/mon/Monitor.h
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
#ifndef _IAS_SM_Mon_Monitor_H_
#define _IAS_SM_Mon_Monitor_H_

#include <commonlib/commonlib.h>
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Cfg{
class Config;
}
namespace Mon {
class ServiceStatus;
class ServiceInstanceObserver;

/*************************************************************************/
/** The Monitor class.
 *
 */
class Monitor {
public:

	virtual ~Monitor() throw();

	void refresh();

	const ServiceStatus* getServiceStatus(const ::org::invenireaude::sm::cfg::Service*) const;

	const Cfg::Config* getConfig()const;

protected:
	Monitor(const Cfg::Config* pConfig);
	void init(const Cfg::Config* pConfig);

	const Cfg::Config* pConfig;

	typedef HashMapOfPointers< const ::org::invenireaude::sm::cfg::Service*, ServiceStatus> ServiceStatusMap;
	ServiceStatusMap hmServiceStatus;

	IAS_DFT_FACTORY<ServiceInstanceObserver>::PtrHoldersCollection phcObservers;

	friend class ::IAS::Factory<Monitor>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Mon_Monitor_H_ */
