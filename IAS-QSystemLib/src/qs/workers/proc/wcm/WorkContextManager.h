/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/WorkContextManager.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_WorkContextManager_H_
#define _IAS_QS_Workers_Proc_WCM_WorkContextManager_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>
#include <map>
#include <set>
#include <unordered_map>

#include <qs/workers/proc/io/IOManager.h>
#include <qs/workers/proc/ds/DSManager.h>

#include "cache/Context.h"
#include "io/Context.h"
#include "ds/Context.h"
#include "storage/Context.h"
#include "txm/Context.h"
#include "task/Context.h"

#include <org/invenireaude/qsystem/workers/io/Parameters.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {

class GlobalContext;

namespace WCM {

namespace IO   { class Manager; }
namespace DS   { class Manager; }
namespace TXM  { class Manager; }


/*************************************************************************/
/** The WorkContextManager class.
 *
 */
class WorkContextManager {

public:

	virtual ~WorkContextManager() throw();


	GlobalContext*        getGlobalContext();

	void begin();
	void commit();
	void rollback();

	WCM::IO::Context    qs;
	WCM::DS::Context    ds;
	WCM::TXM::Context   txm;

	WCM::Cache::Context   caches;
	WCM::Storage::Context storage;
	WCM::Task::Context    task;

	Proc::IO::IOManager*   getIOManager()const;
	Proc::DS::DSManager*   getDSManager()const;

protected:

	WorkContextManager(GlobalContext *pGlobalContext);

	GlobalContext *pGlobalContext;

	IAS_DFT_FACTORY<IO::Manager>::PtrHolder    ptrIOManager;
	IAS_DFT_FACTORY<DS::Manager>::PtrHolder    ptrDSManager;
	IAS_DFT_FACTORY<TXM::Manager>::PtrHolder   ptrTXMManager;

	friend class Factory<WorkContextManager>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_WCM_WorkContextManager_H_ */
