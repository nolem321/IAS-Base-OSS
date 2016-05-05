/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/SharedMemory.h
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
#ifndef _IAS_IPC_SharedMemory_H_
#define _IAS_IPC_SharedMemory_H_

#include "ResourceDescriptor.h"

namespace IAS {
namespace IPC {
/*************************************************************************/
/** The SharedMemory class.
 *
 */
class SharedMemory {
public:


	/*************************************************************************/

	class Descriptor : public ResourceDescriptor {
	public:

		Descriptor(Mode iMode = M_USER)throw();

		void setSize(int iSize);
		void setAddress(void* pAddress);

		void* getAddress()const;
		int   getSize()const;

	protected:

	private:
		int   iSize;
		void* pAddress;
	};

	/*************************************************************************/

	virtual ~SharedMemory() throw();
	SharedMemory(const Descriptor& aDescriptor);

	int getSize()      const;
	void* getAddress() const;
protected:

	void init();
	void refreshInfo();

	int iShmId;
	int iSize;
	void *pAddress;

	Descriptor aDescriptor;

};

/*************************************************************************/
}
}

#endif /* _IAS_SharedMemory_H_ */
