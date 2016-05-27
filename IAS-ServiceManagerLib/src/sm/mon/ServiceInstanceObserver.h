/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ServiceInstanceObserver.h
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
#ifndef _IAS_SM_Mon_ServiceInstanceObserver_H_
#define _IAS_SM_Mon_ServiceInstanceObserver_H_

#include <commonlib/commonlib.h>
#include "sm/cfg/dataobjects.h"

namespace IAS {
namespace SM {
namespace Mon {
class ProcessLockFile;
class ServiceStatus;
class Monitor;
/*************************************************************************/
/** The ServiceInstanceObserver class.
 *
 */
class ServiceInstanceObserver {
public:

	virtual ~ServiceInstanceObserver() throw();

	void refresh();


protected:

	ServiceInstanceObserver(const Monitor *pMonitor,
							ServiceStatus* pServiceStatus,
							int iInstanceIdx);

	const Monitor* pMonitor;
	ServiceStatus* pServiceStatus;
	unsigned int iInstanceIdx;

	IAS_DFT_FACTORY<ProcessLockFile>::PtrHolder ptrLockFile;

	static String           MyServiceName;
	static ProcessLockFile *MyProcessLockFile;

	String strServiceName;
	friend class ::IAS::Factory<ServiceInstanceObserver>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_SM_Mon_ServiceInstanceObserver_H_ */
