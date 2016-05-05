/*
 * File: IAS-CommonLib/src/commonlib/threads/Condition.h
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
#ifndef _IAS_THREAD_Condition_H_
#define _IAS_THREAD_Condition_H_

/*
 *
 */

#include "ThreadLockException.h"
#include <commonlib/time/TimeSamplesRegister.h>

#include "Mutex.h"

namespace IAS {

class Mutex;

/** The class. */
 class Condition  {
public:
	Condition(bool bShared=false);
	~Condition()throw();

	void signal()           throw(ThreadLockException);
	void broadcast()        throw(ThreadLockException);

protected:

	void wait(Mutex& mutex)throw(ThreadLockException);
	bool wait(Mutex& mutex, unsigned int iTimeoutMS) throw(ThreadLockException);

	pthread_cond_t theCond;

	friend class Mutex;
};

}

#endif /* THREADSAFELOCKWITHWAIT_H_ */
