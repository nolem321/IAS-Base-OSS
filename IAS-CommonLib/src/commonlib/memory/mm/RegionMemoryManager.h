/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/RegionMemoryManager.h
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
#ifndef _IAS_RegionMemoryManager_H_
#define _IAS_RegionMemoryManager_H_


#include "commonlib/threads/Mutex.h"
#include "../ma/Allocator.h"

namespace IAS {

/*************************************************************************/
/** The RegionMemoryManager class.
 *
 */
class RegionMemoryManager : public Allocator {
public:


	virtual ~RegionMemoryManager()throw();

	virtual void* allocate(size_t n);
	virtual void  free(const void* p);
	virtual bool  check(const void* p);

	virtual void  freeAll();

	virtual void  printToStream(std::ostream& os);


	void dump(std::ostream& os);

	RegionMemoryManager(Allocator *pSegmentManager,
							size_t iSegmentSize=(1L<<16));

protected:

	class Segment{
	public:
		 Segment(size_t iSize):pNext(0),iSize(iSize){};

		 void setNext(Segment* pNext){this->pNext=pNext;}
		 Segment* getNext()const{ return pNext; }

		 size_t getSize()const{ return iSize;};
		 char  *getData(){ return (char*)(this+1);}
	protected:
		 size_t   iSize;
		 Segment* pNext;
	};

	Mutex          mutex;

	TimeSamplesResults  tsrMutexWaits;
	TimeSamplesResults  tsrAllocations;

	unsigned int        iNumSegments;
	unsigned int        iNumSegmentsWaterMark;

	Allocator *pSegmentAllocator;

	size_t        iSegmentSize;
	Segment		  *pHead;
	Segment		  *pTail;
	size_t        iOffset;

	unsigned int  iMinKeptSegments;

	void allocateSegment(size_t iSegmentSize);
	void deleteSegments(unsigned int iSkip);

	//friend class Factory<RegionMemoryManager>;
};

/*************************************************************************/
}

#endif /* _IAS_RegionMemoryManager_H_ */
