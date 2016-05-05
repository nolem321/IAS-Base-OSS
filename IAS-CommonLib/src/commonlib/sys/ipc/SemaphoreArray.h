/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/SemaphoreArray.h
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
#ifndef _IAS_IPC_SemaphoreArray_H_
#define _IAS_IPC_SemaphoreArray_H_

#include "ResourceDescriptor.h"
#include "commonlib/sys/Locker.h"

namespace IAS {
namespace IPC {
/*************************************************************************/
/** The SemaphoreArray class.
 *
 */
class SemaphoreArray {
public:

	/*************************************************************************/

	class Descriptor : public ResourceDescriptor {
	public:
		Descriptor(Mode iMode = M_USER)throw();

		void setNumSem(int iNumSem);
		int getNumSem() const;

	protected:

	private:
		int iNumSem;
	};

	/*************************************************************************/

	class Semaphore : public ::IAS::SYS::ILockable {

	public:

		virtual void lock();
		virtual void unlock();

		Semaphore(const Semaphore& other);

		void reset();

		void inc();
		void dec();
		bool decNoWait();
		int  get() const;

		protected:

		Semaphore(int iSemId, int iIdx);
		int iSemId;
		int iIdx;

		friend class SemaphoreArray;
	};

	/*************************************************************************/

	virtual ~SemaphoreArray() throw();
	SemaphoreArray(const Descriptor& aDescriptor);

	void resetAll();

	Semaphore operator[](int iIdx);

protected:

	void init();

	int iSemId;
	int iNumSem;
	Descriptor aDescriptor;

};

/*************************************************************************/
}
}

#endif /* _IAS_SemaphoreArray_H_ */
