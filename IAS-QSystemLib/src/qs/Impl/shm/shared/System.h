/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/System.h
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
#ifndef _IAS_QS_System_Shared_System_H_
#define _IAS_QS_System_Shared_System_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace SHM {
class Attachment;
namespace Shared {

class QueueTable;
class SessionTable;
class ContentStorage;

/*************************************************************************/

struct SharedMemorySegment{
	SharedMemorySegment();
	void     *pAddress;
	size_t   iSize;
};

/*************************************************************************/
/** The System class.
 *
 */
class System {
public:

	struct Version{

		typedef unsigned char Number;

		Version(Number iMajor,
				Number iMinor,
				Number iRelease);

		Version(const Version& other);

		Number iMajor;
		Number iMinor;
		Number iRelease;

		String toString()const;

		bool isCompatible(const Version& other)const;
	};

protected:

	System(const String& strName);
	~System();

	Version         systemVersion;

	static const int C_MaxSysNameLength = 24;
	char sName[C_MaxSysNameLength+1];

	SharedMemorySegment  shmSystemHeap;
	SharedMemorySegment  shmQueueData;
	SharedMemorySegment  shmApplicationData;

	Mutex mutexSystem;

	QueueTable     *pQueueTable;
	SessionTable   *pSessionTable;
	ContentStorage *pContentStorage;



	const static Version CSoftwareVersion;

	friend class ::IAS::QS::SHM::Attachment;
	friend class Factory<System>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_System_SystemShared_H_ */
