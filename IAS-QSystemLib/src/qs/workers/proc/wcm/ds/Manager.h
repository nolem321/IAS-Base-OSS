/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/ds/Manager.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_DS_Manager_H_
#define _IAS_QS_Workers_Proc_WCM_DS_Manager_H_

#include <commonlib/commonlib.h>

#include <qs/workers/proc/ds/DSManager.h>
#include <qs/workers/proc/ds/DSFactory.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace DS {

class Context;

/*************************************************************************/
/** The Manager class.
 *
 */
class Manager :
		public Proc::DS::DSManager{

	public:

	virtual ~Manager() throw();

	virtual Proc::DS::DSDriver *getDSDriver(const String& strName)const;
	virtual void addDSDriver(const String& strName, Proc::DS::DSDriver *pDSDriver);

protected:

	Manager(WorkContextManager* pWorkContextManager);
	WorkContextManager* pWorkContextManager;

	friend class Factory<Manager>;

	typedef HashMapStringToPointer<Proc::DS::DSDriver>     DSDriversMap;
	DSDriversMap                                           hmDSDrivers;

	IAS_DFT_FACTORY<Proc::DS::DSFactory>::PtrHolder        ptrFactory;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_WCM_DS_Manager_H_ */
