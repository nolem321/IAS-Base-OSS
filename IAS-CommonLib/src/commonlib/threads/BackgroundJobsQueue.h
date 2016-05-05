/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobsQueue.h
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
#ifndef _IAS_BACKGROUNDJOBSQUEUE_H_
#define _IAS_BACKGROUNDJOBSQUEUE_H_

#include "Condition.h"

#include "../memory/memory.h"


namespace IAS {

class BackgroundJobEntry;
class BackgroundJobThread;

/*************************************************************************/
/** The class. */
 class BackgroundJobsQueue {
public:

	BackgroundJobsQueue(int iQueueSize);
	virtual ~BackgroundJobsQueue() throw();

	void addEntry(BackgroundJobEntry *pEntry);
	BackgroundJobEntry *assignEntry(BackgroundJobThread *pThread);

	void releaseEntry(BackgroundJobEntry *pEntry);
	void removeEntry(BackgroundJobEntry *pEntry);

	void close();

protected:


	Mutex     theLock;
	Condition theConditionEmpty;

	IAS_DFT_FACTORY<BackgroundJobEntry>::PtrHoldersCollection phcJobEntries;


	int iQueueSize;
	int iNumEntries;

	bool bClosed;

	friend class Factory<BackgroundJobsQueue>;
};

/*************************************************************************/
}

#endif /* _IAS_BACKGROUNDJOBSQUEUE_H_ */
