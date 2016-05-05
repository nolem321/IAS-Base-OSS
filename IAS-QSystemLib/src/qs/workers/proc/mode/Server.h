/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/Server.h
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
#ifndef _IAS_QS_Workers_Proc_Mode_Server_H_
#define _IAS_QS_Workers_Proc_Mode_Server_H_

#include <commonlib/commonlib.h>

#include "ModeBase.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {

class GlobalContext;

namespace Mode  {

/*************************************************************************/
/** The Server class.
 *
 */
class Server : public ModeBase {
public:

	virtual ~Server() throw();

	virtual void run();

protected:

	Server(GlobalContext *pGlobalContext,
	     	 int iLogicIdx);

	//ThreadSpecific<Workers::Proc::WorkContextManager>::Pointer  pThreadContext;

	IAS_DFT_FACTORY<RegionMemoryManager>::PtrHolder ptrMemoryManager;

	friend class Factory<Server>;

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Mode_Server_H_ */
