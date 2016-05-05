/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/txm/Manager.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_TXM_Manager_H_
#define _IAS_QS_Workers_Proc_WCM_TXM_Manager_H_

#include <commonlib/commonlib.h>

#include <qs/workers/proc/txm/TXMManager.h>
#include <qs/workers/proc/txm/TXMFactory.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace TXM {

/*************************************************************************/
/** The Manager class.
 *
 */
class Manager :	public Proc::TXM::TXMManager{

	public:

	virtual ~Manager() throw();
	virtual Proc::TXM::TXMDriver *getTXMDriver(const String& strName)const;
	virtual void addTXMDriver(const String& strName, Proc::TXM::TXMDriver *pTXMDriver);

protected:

	Manager(WorkContextManager* pWorkContextManager);
	WorkContextManager* pWorkContextManager;

	friend class Factory<Manager>;

	typedef HashMapStringToPointer<Proc::TXM::TXMDriver>   TXMDriversMap;
	TXMDriversMap                                    	   hmTXMDrivers;

	IAS_DFT_FACTORY<Proc::TXM::TXMFactory>::PtrHolder      ptrFactory;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_WCM_TXM_Manager_H_ */
