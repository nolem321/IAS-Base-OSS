/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/ContentStorage.h
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
#ifndef _IAS_QS_System_Shared_ContentStorage_H_
#define _IAS_QS_System_Shared_ContentStorage_H_

#include <commonlib/commonlib.h>
#include <qs/api/Content.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

/*************************************************************************/
/** The ContentStorage class.
 *
 */
class ContentStorage {
public:


	struct Entry;

	struct Descriptor{

		Descriptor():pEntry(0){};
		~Descriptor();

		Descriptor(Entry* pEntry);
		Descriptor(const Descriptor& other);
		Descriptor& operator=(const Descriptor& other);

		Entry* getEntry();

		inline bool operator!()const{
			return !pEntry;
		}

		//TODO private & getters/setters
	private:
		Entry* pEntry;
	};


	ContentStorage(int iMaxEntries);
	~ContentStorage() throw();

	struct Entry{
		Entry();
		Mutex      mutex;
		void       *pMemorySlot;
		int        iUsageCount;
		bool bUsed;
		void incUsageCount();
		int  decUsageCount();
		int  getUsageCount();

	};

	Descriptor allocateNew();

	void dump(std::ostream& os);

protected:

	int iMaxEntries;
	int iNumErrors;

	Mutex                      mutex;

	TimeSamplesResults tsrMutexWaits;
	TimeSamplesResults tsrAllocations;

	Entry *tabEntries;

};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_System_Shared_ContentStorage_H_ */
