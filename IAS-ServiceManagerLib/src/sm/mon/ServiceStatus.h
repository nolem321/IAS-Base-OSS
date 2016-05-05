/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ServiceStatus.h
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
#ifndef _IAS_SM_Mon_ServiceStatus_H_
#define _IAS_SM_Mon_ServiceStatus_H_

#include <commonlib/commonlib.h>
#include "sm/cfg/dataobjects.h"
#include <vector>

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
/** The ServiceStatus class.
 *
 */
class ServiceStatus {
public:

	struct InstanceStatus{
		bool         bIsStarted;
		bool         bIsRunning;
		unsigned int iPid;
	};


	virtual ~ServiceStatus() throw();

	const ::org::invenireaude::sm::cfg::Service* getService()const;

	InstanceStatus* getInstanceStatus(unsigned int iIdx);

	const InstanceStatus* getInstanceStatus(unsigned int iIdx)const;

protected:
	ServiceStatus(const ::org::invenireaude::sm::cfg::Service* pService, int iCount);

	const ::org::invenireaude::sm::cfg::Service* pService;

	std::vector<InstanceStatus> tabInstancesStatus;

	friend class ::IAS::Factory<ServiceStatus>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Mon_ServiceStatus_H_ */
