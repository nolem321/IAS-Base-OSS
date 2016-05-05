/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobsExecutor.h
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
#ifndef _IAS_BackgroundJobsExecutor_H_
#define _IAS_BackgroundJobsExecutor_H_

#include "Runnable.h"
#include "Thread.h"
#include "Mutex.h"

#include "../logger/logger.h"
#include "../memory/memory.h"
#include "../memory/ma/PtrHolder.h"
#include "../containers/PtrVector.h"

#include "commonlib/memory/ma/Factory.h"

#include <vector>

namespace IAS {

class BackgroundJob;
class BackgroundJobsQueue;
class BackgroundJobThread;

/*************************************************************************/
/** The class. */
 class BackgroundJobsExecutor {
public:

	BackgroundJobsExecutor(int iNumThreads, int iQueueSize = 100);
	virtual ~BackgroundJobsExecutor() throw();

	void enqueue(BackgroundJob *pJob);

	void setCompleteJobsOnDelete(bool bCompleteJobsOnDelete);

protected:

	void init(int iQueueSize);

	typedef PtrVector<BackgroundJobThread> ThreadsTab;
	ThreadsTab tabThreads;

	int iNumThreads;

	IAS_DFT_FACTORY<BackgroundJobsQueue>::PtrHolder ptrQueue;

	bool bCompleteJobsOnDelete;

	friend class Factory<BackgroundJobsExecutor>;
};

/*************************************************************************/
}

#endif /* _IAS_BACKGROUNDJOBSEXECUTOR_H_ */
