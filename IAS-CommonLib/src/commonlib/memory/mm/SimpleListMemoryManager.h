/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/SimpleListMemoryManager.h
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
#ifndef _IAS_SimpleListMemoryManager_H_
#define _IAS_SimpleListMemoryManager_H_

#include "../ma/Allocator.h"
#include "MemoryManager.h"

#include "commonlib/threads/Mutex.h"

namespace IAS {

/*************************************************************************/
/** The SimpleListMemoryManager class.
 *
 */
class SimpleListMemoryManager : public Allocator {
public:

	virtual ~SimpleListMemoryManager()throw();

	virtual void* allocate(size_t n);
	virtual void  free(const void* p);
	virtual bool  check(const void* p);

	static void Initialize(void *pStart, size_t iSize);


	virtual void printToStream(std::ostream& os);

	void dump(std::ostream& os);
protected:

	SimpleListMemoryManager(void *pStart, size_t iSize);
	SimpleListMemoryManager(void *pStart);

	friend class Factory<SimpleListMemoryManager>;

	typedef int EntryIndex;

	struct Entry{

		EntryIndex iSize;

		Entry *next;
		Entry *prev;

		inline void free()     { iSize=abs(iSize); };
		inline void allocate() { iSize=-abs(iSize); };
		inline bool isFree()   { return iSize > 0; };

		inline size_t getSize(){ return abs(iSize); }
	};

	Entry*      tabEntries;


	struct Info{

		static const int   C_TagSize=4;
		static const char  C_Tag[C_TagSize+1];

		Info();

		char sTag[4];

		EntryIndex  iNumEntries;
		size_t      iSpaceSize;

		size_t      iAllocated;
		size_t      iWaterMark;

		Entry   *head;
		Entry   *tail;

		Entry   *last;

		Mutex mutex;
		TimeSamplesResults  tsrMutexWaits;
		TimeSamplesResults  tsrAllocations;
		TimeSamplesResults  tsrSearchesNoSplit;
		TimeSamplesResults  tsrSearches;
	};

	Info*      pInfo;

	static const int FAST_ALLOC=4;
};

/*************************************************************************/
}

#endif /* _IAS_SimpleListMemoryManager_H_ */
