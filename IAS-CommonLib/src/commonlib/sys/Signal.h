/*
 * File: IAS-CommonLib/src/commonlib/sys/Signal.h
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
#ifndef _IAS_SYS_Signal_H_
#define _IAS_SYS_Signal_H_

#include "../misc/InstanceFeature.h"

#include <set>
namespace IAS {
class Thread;

namespace SYS {

/*************************************************************************/
/** The Signal class.
 *
 */
class Signal : public InstanceFeature<Signal>{
public:

	virtual ~Signal() throw();

	bool isStopping()const;

	class ThreadRegistration{
	public:
		ThreadRegistration();
		~ThreadRegistration();
	};

	static void SignalHandler(int iSignal = 0);

	static Signal* GetInstance();

protected:
	Signal();

	typedef std::set<Thread*> ThreadSet;
	ThreadSet                 setThreadsToStop;

	void addThread(Thread* pThread);
	void removeThread(Thread* pThread);

	void stopThreads();

	friend class Factory<Signal>;

	static bool bStopping;
};

/*************************************************************************/
}
}

#endif /* _IAS_SYS_Signal_H_ */
