/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobThread.h
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
#ifndef _IAS_BACKGROUNDJOBTHREAD_H_
#define _IAS_BACKGROUNDJOBTHREAD_H_

#include "commonlib/memory/ma/Factory.h"

#include "Runnable.h"
#include "Thread.h"
#include "Mutex.h"

namespace IAS {

class BackgroundJobEntry;
class BackgroundJobsQueue;

/*************************************************************************/
/** The class. */
 class BackgroundJobThread : public Runnable , public Thread {
public:

	virtual ~BackgroundJobThread() throw();

	void run();

	void setEndOfWorkState();

protected:

	/*//TODO (L) think about auto release
	class EntryHolder{
	public:
		EntryHolder() throw();
		~EntryHolder() throw();
		set
		BackgroundJobEntry *pEntry;
	};
	*/

	BackgroundJobThread(BackgroundJobsQueue* pQueue);

	void startJob(BackgroundJobEntry *pEntry);
	void cancelJob(BackgroundJobEntry *pEntry);
	void removeJob(BackgroundJobEntry *pEntry);

	BackgroundJobsQueue* pQueue;

	bool bEndOfWork;

	bool getEndOfWorkState();

	Mutex theLock;

	friend class Factory<BackgroundJobThread>;
};

/*************************************************************************/
}

#endif /* _IAS_BACKGROUNDJOBTHREAD_H_ */
