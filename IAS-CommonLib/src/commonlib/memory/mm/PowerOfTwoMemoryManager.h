/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/PowerOfTwoMemoryManager.h
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
#ifndef _IAS_PowerOfTwoMemoryManager_H_
#define _IAS_PowerOfTwoMemoryManager_H_

#include "../ma/Allocator.h"
#include "MemoryManager.h"
#include "commonlib/threads/Mutex.h"

namespace IAS {

/*************************************************************************/
/** The PowerOfTwoMemoryManager class.
 *
 */
class PowerOfTwoMemoryManager : public Allocator {
public:

	virtual ~PowerOfTwoMemoryManager()throw();

	virtual void* allocate(size_t n);
	virtual void  free(const void* p);
	virtual bool  check(const void* p);

	static void Initialize(void *pStart, size_t iSize, int iLgBaseSize=6);


	virtual void printToStream(std::ostream& os);

	void dump(std::ostream& os);
protected:

	PowerOfTwoMemoryManager(void *pStart, size_t iSize);
	PowerOfTwoMemoryManager(void *pStart);

	friend class Factory<PowerOfTwoMemoryManager>;

	typedef int32_t ListIndex;

	typedef unsigned char Byte;


	class List{
	public:
		inline List():prev(0),next(0){};

		inline bool empty()const {
			return prev==0;
		}

		inline void link(List* pList){

			ListIndex diff=this-pList;

			next=-diff;
			prev=-diff+pList->prev;

			(this+prev)->next=-prev;
			pList->prev=-next;
		}

		inline void unlink(){
			(this+next)->prev=prev-next;;
			(this+prev)->next=next-prev;
			prev=0;
			next=0;
		}

		inline List* head(){
			return this+next;
		}

		void _print(std::ostream& os, List* pBase){
			List *c=this;
			do{
				os<<" "<<(c-pBase)<<":["<<c->prev<<","<<c->next<<"]";
				c=c+c->next;
			}while(c!=this);
		}

	protected:
		ListIndex prev;
		ListIndex next;

	};

	class Segment {

	public:

		Segment();

		static const unsigned short C_LgBitMapSize=10;

		unsigned int allocateBlock();
		void freeBlock(unsigned int    iBlock);
		bool isUsed(unsigned int    iBlock);

		void setBucket(Byte iBucket);
		Byte getBucket()const {return iBucket;};

		inline unsigned int getSize()const{
			return 1L<<(C_LgBitMapSize-iBucket);
		};

		inline unsigned int getAllocated()const {  return iNumAllocated; };

		inline bool isFull()const {  return iNumAllocated == getSize(); };
		inline bool isEmpty()const { return !iNumAllocated; };


	protected:

		short          iLgBlockSize;
		Byte		   iBucket;

		unsigned int   iNumAllocated;
		Byte tBitMap[1L<<C_LgBitMapSize/sizeof(Byte)];
	};

	struct Info{

		static const int   C_TagSize=4;
		static const char  C_Tag[C_TagSize+1];

		Info();

		char sTag[4];

		size_t      iSpaceSize;
		size_t      iAllocated;
		size_t      iWaterMark;


		List		*pFreeList;
		List	    *pAllocatedBySizeList;
		List	    *pSegmentList;
		Segment     *pSegments;

		Byte		*pData;

		int			iLgBaseSize;
		int			iSegments;
		int			iSegmentSize;
		int			iBuckets;

		Mutex mutex;

		TimeSamplesResults  tsrMutexWaits;
		TimeSamplesResults  tsrAllocations;

		void* allocate(size_t n);
		void  free(const void* p);
		bool  check(const void* p);

		void *encodeAddress(unsigned int iSegment, unsigned int iBlock);
		void  decodeAddress(const void *pAddress, unsigned int& iSegment, unsigned int& iBlock);

		unsigned int getSegment(List* pList);
	};

	Info*      pInfo;
};

/*************************************************************************/
}

#endif /* _IAS_PowerOfTwoMemoryManager_H_ */
