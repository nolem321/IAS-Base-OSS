/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/SessionData.h
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
#ifndef _IAS_QS_SessionData_Shared_SessionData_H_
#define _IAS_QS_SessionData_Shared_SessionData_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
class Queue;

class JournalObjectEntry;

/*************************************************************************/
/** The SessionData class.
 *
 */
class SessionData {
public:

	typedef unsigned short int SessionDataSize;

	SessionData();
	~SessionData();

	JournalObjectEntry* allocateJOE();

	void rollback();
	void commit();

protected:

	SessionData(SessionDataSize iObjectEntires, SessionDataSize iDataEntires);

	SessionDataSize iObjectEntires;
	SessionDataSize iDataEntires;

	JournalObjectEntry *tabObjectJournal;

	friend class IAS::Factory<SessionData>;
};


}
}
}
}

#endif /* _IAS_QS_SessionData_SessionDataShared_H_ */

