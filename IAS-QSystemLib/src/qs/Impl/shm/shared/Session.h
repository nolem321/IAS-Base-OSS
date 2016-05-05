/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/Session.h
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
#ifndef _IAS_QS_Session_Shared_Session_H_
#define _IAS_QS_Session_Shared_Session_H_

#include <commonlib/commonlib.h>
#include "SessionData.h"

#include "../Attachment.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

class MsgEntry;
class Subscription;


/*************************************************************************/
/** The Session class.
 *
 */
class Session {
public:

	typedef unsigned short int SessionSize;
	typedef short unsigned int ID;

	enum Mode{
		SM_NotAllocated,
		SM_Transacted,
		SM_AutoCommit
	};

	Session();
	~Session();

	void setupTransacted();
	void setupAutoCommit();

	void commit();
	void rollback();

	void close();
	void tryToClean();

	JournalObjectEntry* allocateJOE();

	class Holder{
		public:

			Holder(Session* pSession = 0)
			:pSession(pSession){};

			~Holder(){	close();  }

			void set(Session  *pSession){
				close();
				this->pSession=pSession;
			}

			bool operator!()const { return pSession == NULL; }

			Session* operator=(Session *pSession){ set(pSession); return pSession;}

			inline Session* operator->(){
				IAS_CHECK_IF_NULL(pSession);
				return pSession;
			};

		private:

			Session      *pSession;
			inline void close(){
				if(pSession){
					pSession->close();
				}
			}

		};

	/*
	 * Some utilities.
	 */

	inline bool isAllocated(){
		Mutex::Locker locker(mutex);
		return isAllocatedNoLock();
	 }

	inline bool isFree() {
		Mutex::Locker locker(mutex);
		return iMode == SM_NotAllocated;
	 }

	inline bool isType(Mode iMode) {
		Mutex::Locker locker(mutex);
		return this->iMode == iMode;
	 }


protected:

	Mutex mutex;
	Mode iMode;

	Mutex mutexAlive;

	QS::SHM::QueueAllocator<SessionData>::PtrHolder ptrSessionData;

	inline bool isAllocatedNoLock(){
		return iMode != SM_NotAllocated;
	 }

	void setupNoLock(Mode iMode);
	void rollbackNoLock();
	void closeNoLock();
};


}
}
}
}

#endif /* _IAS_QS_Session_SessionShared_H_ */

