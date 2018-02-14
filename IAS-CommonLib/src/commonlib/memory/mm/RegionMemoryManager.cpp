/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/RegionMemoryManager.cpp
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
#include "RegionMemoryManager.h"
#include "../ma/Allocator.h"
#include "commonlib/exception/InternalException.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>

namespace IAS {

/*************************************************************************/
RegionMemoryManager::RegionMemoryManager(Allocator *pSegmentAllocator,
										 size_t iSegmentSize):
	pSegmentAllocator(pSegmentAllocator),
	iSegmentSize(iSegmentSize),
	iNumSegments(0),
	iNumSegmentsWaterMark(0),
	iOffset(0),
	pHead(0),
	iMinKeptSegments(2),
	pTail(0){

	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSegmentAllocator);

	bDisabledDestructors=true;
	bCheckPointersOnReturn=false;

	allocateSegment(iSegmentSize);
}
/*************************************************************************/
RegionMemoryManager::~RegionMemoryManager()throw(){
	IAS_TRACER;
	deleteSegments(0);
}
/*************************************************************************/
void RegionMemoryManager::allocateSegment(size_t iSegmentSize){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"New segment, size="<<iSegmentSize);

	iOffset=0;

	if(pTail){

		Segment *pCursor=pTail->getNext();

		while(pCursor){

			pTail=pCursor;

			if(pCursor->getSize() >= iSegmentSize){
				IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Reusing at:"<<(void*)(pTail->getData()));
				return;
			}

			pCursor=pCursor->getNext();
		}
	}


	Segment *pNew = new(pSegmentAllocator->allocate(sizeof(Segment)+iSegmentSize)) Segment(iSegmentSize);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Data start="<<(void*)pNew->getData());

	IAS_CHECK_IF_NULL(pNew);

	if(!pHead){
		pHead=pNew;
		pTail=pNew;
	}else{
		pTail->setNext(pNew);
		pTail=pNew;
	}
	iNumSegments++;
}
/*************************************************************************/
void RegionMemoryManager::deleteSegments(unsigned int iSkip){
	IAS_TRACER;

	Segment * pCursor=pHead;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Deleting segments, skip="<<iSkip);

	if(!iSkip)
		pHead=0;

	unsigned int iLeft=iSkip;

	while(pCursor && iLeft--){
		Segment *pNext=pCursor->getNext();
		if(!iLeft)
			pCursor->setNext(0);
		pCursor=pNext;
	}

	while(pCursor){
		Segment *pNext=pCursor->getNext();
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Removing: "<<(void*)pCursor);
		pSegmentAllocator->free(pCursor);
		iNumSegments--;
		pCursor=pNext;
	}

	iNumSegments=iSkip;
}
/*************************************************************************/
void* RegionMemoryManager::allocate(size_t n){


	IAS_LOG(LogLevel::INSTANCE.isMemory(),"Allocate size="<<n);

	Mutex::Locker locker(mutex, tsrMutexWaits);
	AutoTimeSample sample(tsrAllocations,LogLevel::INSTANCE.isProfile());

	if(n > iSegmentSize){
		allocateSegment(n + iSegmentSize);
	}else if(iOffset + n > iSegmentSize){
		allocateSegment(iSegmentSize);
	}

	void *pResult = pTail->getData()+iOffset;
	iOffset+=n;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"offset="<<iOffset<<", segsize="<<pTail->getSize());

	return pResult;
}
/*************************************************************************/
void  RegionMemoryManager::freeAll(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isMemory(),"  ** Free All **, head="<<(void*)pHead->getData());

	pTail=pHead;
	iOffset=0;

}
/*************************************************************************/
void  RegionMemoryManager::free(const void* p){
	IAS_TRACER;
}
/*************************************************************************/
bool  RegionMemoryManager::check(const void* p){

	Mutex::Locker locker(mutex, tsrMutexWaits);

	Segment *pCursor=pHead;

	while(pCursor){

		size_t iOffset=(char*)p-pCursor->getData();

		if(iOffset >= 0 && iOffset < pCursor->getSize())
			return true;

		pCursor=pCursor->getNext();
	}

	pCursor=pHead;
	while(pCursor){

		size_t iOffset=(char*)p-pCursor->getData();

		IAS_LOG(LogLevel::INSTANCE.isError(),"This is not my pointer: "<<p<<","<<iOffset);

		pCursor=pCursor->getNext();
	}

	IAS_LOG(LogLevel::INSTANCE.isError(),"This is not my pointer: "<<p<<", this= "<<(void*)this);
	IAS_MY_STACK().printStack(std::cerr);
	IAS_THROW(InternalException("This is not my pointer!"));
	((char*)0)[10]=0;
	return false;
}
/*************************************************************************/
void RegionMemoryManager::printToStream(std::ostream& os){

	os<<"  Segments:     "<<iNumSegments<<", offset: "<<iOffset<<std::endl;
	os<<"  Waits:        "<<tsrMutexWaits<<std::endl;
	os<<"  Allocations:  "<<tsrAllocations<<std::endl;
	os<<std::endl;
}
/*************************************************************************/
void RegionMemoryManager::dump(std::ostream& os){

	Segment *pCursor=pHead;

	while(pCursor){
		os<<(void*)pCursor->getData()<<", "<<pCursor->getSize()<<(pCursor==pTail ? "  <== Tail" : "")<<std::endl;
		pCursor=pCursor->getNext();
	}
}
/*************************************************************************/
}
