/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/JournalObjectEntry.h
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
#ifndef _IAS_QS_SHM_Shared_JournalObjectEntry_H_
#define _IAS_QS_SHM_Shared_JournalObjectEntry_H_

#include <commonlib/commonlib.h>
#include "Queue.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

/*************************************************************************/
/** The JournalObjectEntry class.
 *
 */
class JournalObjectEntry {
public:

	enum Type{
		JOE_Free,
		JOE_AllocatedUnused,
		JOE_OpenedQueue
	};

	JournalObjectEntry();

	class Holder{
		public:
		 Holder(JournalObjectEntry* pEntry):pEntry(pEntry){}

		bool operator!()const {
			IAS_CHECK_IF_NULL(pEntry);
			return pEntry->iType != JOE_OpenedQueue;
		}

		void assignQueue(Queue* pQueue,bool bRemoveOnClose){
			IAS_CHECK_IF_NULL(pEntry);
			pEntry->set(pQueue, bRemoveOnClose);
		}

		Queue *operator->(){

			 if(!pEntry || pEntry->free())
				 IAS_THROW(InternalException("JOE is free in Holder."))

			return pEntry->pQueue;
		}

		~Holder(){

			if(!pEntry)
				return;

			pEntry->rollback();
		}

		protected:
		JournalObjectEntry *pEntry;
	};

	inline bool free()const{ return iType == JOE_Free; };

	void allocate();

	void set(Queue* pQueue, bool bRemoveOnClose);
	void reset();
	void rollback();

	~JournalObjectEntry() throw();

protected:
	Type      iType;
	Queue*    pQueue;
	bool      bRemoveOnClose;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_SHM_Shared_JournalObjectEntry_H_ */
