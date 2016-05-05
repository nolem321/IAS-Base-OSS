/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/ProcessorWorker.h
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
#ifndef _IAS_QS_Workers_Proc_Mode_ProcessorWorker_H_
#define _IAS_QS_Workers_Proc_Mode_ProcessorWorker_H_

#include <commonlib/commonlib.h>
#include <commonlib/memory/mm/RegionMemoryManager.h>

#include "../logic/LogicFactory.h"
#include <org/invenireaude/qsystem/workers/spec/Specification.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {

class Parameters;
class GlobalContext;

namespace WCM{
class WorkContextManager;
}

namespace Stats{
class LogicStats;
}

namespace Mode {

/*************************************************************************/
/** The ProcessorWorker class.
 *
 */
class ProcessorWorker {
public:

	virtual ~ProcessorWorker() throw();
	void iterate();

protected:

	ProcessorWorker(GlobalContext *pGlobalContext,
				   	   int iLogicIdx);

	Logic::LogicFactory::PtrHolder   ptrLogic;


	ThreadSpecific< WCM::WorkContextManager>::Pointer      pWorkContextShared;
	IAS_DFT_FACTORY< WCM::WorkContextManager >::PtrHolder  ptrWorkContext;

	GlobalContext                                        *pGlobalContext;


	IAS::Allocator* pOriginalAllocator;

	/*This Memory Manager instance should be deleted last, some data may still reside. */
	IAS_DFT_FACTORY<RegionMemoryManager>::PtrHolder      ptrMemoryManager;

	Stats::LogicStats *pLogicStats;

	int iCommitCount;

	String strName;

	friend class Factory<ProcessorWorker>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Mode_ProcessorWorker_H_ */
