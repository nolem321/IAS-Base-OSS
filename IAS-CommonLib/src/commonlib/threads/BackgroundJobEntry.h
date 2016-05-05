/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobEntry.h
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
#ifndef IAS_BACKGROUNDJOBENTRY_H_
#define IAS_BACKGROUNDJOBENTRY_H_

/*
 *
 */
#include "../logger/logger.h"
#include "../memory/memory.h"
#include "../types.h"

#include "commonlib/memory/ma/Factory.h"

#include "Mutex.h"

namespace IAS {

class BackgroundJob;
class BackgroundJobThread;

/** The class. */
 class BackgroundJobEntry {
public:

	enum State{
		JS_Waiting = 0,
		JS_Running = 1
	};

	BackgroundJobEntry(BackgroundJob* pBackgroundJob, int iRetryCount = 10);
	virtual ~BackgroundJobEntry() throw();

	BackgroundJob* getBackgroundJob();

	int getRetryCount();
	int decrementAndGetRetryCount();

	void getId(String& strId);

	void assignOwner(BackgroundJobThread* pThread);
	void releaseOwner();

	int  getState();

protected:

	IAS_DFT_FACTORY<BackgroundJob>::PtrHolder ptrBackgroundJob;

	int iRetryCount;

	String strId;
	State  iState;

	Mutex theLock;

	BackgroundJobThread* pThread;

	friend class ::IAS::Factory<BackgroundJobEntry>;
};

}

#endif /* BACKGROUNDJOBENTRY_H_ */
