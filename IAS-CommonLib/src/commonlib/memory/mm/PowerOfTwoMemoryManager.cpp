/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/PowerOfTwoMemoryManager.cpp
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
#include "PowerOfTwoMemoryManager.h"
#include "commonlib/exception/InternalException.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>
#include <strings.h>

/****************************************************************
 *
 * Data Structure:
 *
 *  Info                       : Info
 *  FreeList                   : List (list head)
 *  SegmentBySize[NumBuckets]  : List (list heads)
 *  AllSegments[NumSegments]   : List (list elements added/removed)
 *
 *  Segment can be either on:
 *  	- free list
 *  	- bySize list  - bucketSize is assigned
 *  	- neither list - when full.
 */


namespace IAS {

/*************************************************************************/
class FFSB {

	char t[0x100];
	static FFSB TheInstance;

	public:

	FFSB(){

		for(int i=0;i<0xff;i++){
			unsigned char n= i & -i;
			if(n & 0x02)t[i]=1;
			if(n & 0x04)t[i]=2;
			if(n & 0x08)t[i]=3;
			if(n & 0x10)t[i]=4;
			if(n & 0x20)t[i]=5;
			if(n & 0x40)t[i]=6;
			if(n & 0x80)t[i]=7;
		}
	}

	static inline char Find(unsigned char &c){
		return TheInstance.t[c];
	}
};

FFSB FFSB::TheInstance;
/*************************************************************************/
PowerOfTwoMemoryManager::Segment::Segment():
	iNumAllocated(0),
	iLgBlockSize(0),
	iBucket(0){
	IAS_TRACER;

	for(int iIdx=0;iIdx < 1L<<C_LgBitMapSize/sizeof(Byte);iIdx++)
		tBitMap[iIdx]=0xff;

}
/*************************************************************************/
unsigned int PowerOfTwoMemoryManager::Segment::allocateBlock(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Full: "<<iNumAllocated<<" ? "<<getSize());

	if(iNumAllocated==getSize())
		IAS_THROW(InternalException("This segment is full."))
	++iNumAllocated;

	Byte *p=tBitMap;
	int iBlock=0;
	int iNumBlocks=1L<<(C_LgBitMapSize/sizeof(Byte)-iBucket);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"iNumBlocks="<<iNumBlocks);

	for(int iIdx=0; iIdx < iNumBlocks;iIdx++){

		if(*p){
			char iBit=FFSB::Find(*p);
			*p^=0x1<<iBit;
			iBlock+=iBit;
			return iBlock;
		}

		iBlock+=8;
		p++;
	}

	IAS_THROW(InternalException("iNumAllocated mismatch !"));
}
/*************************************************************************/
void PowerOfTwoMemoryManager::Segment::freeBlock(unsigned int iBlock){
	IAS_TRACER;
	if(iBlock > getSize())
		IAS_THROW(InternalException("Block number of range in PowerOfTwoMemoryManager::Segment::freeBlock."))

	if(tBitMap[iBlock>>3] & (0x01 <<(iBlock & 0x07)))
		IAS_THROW(InternalException("Block was not allocated."))

	tBitMap[iBlock>>3] |= 0x1<<(iBlock & 0x07);

	--iNumAllocated;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Empty: "<<iNumAllocated<<" ? "<<getSize());
}
/*************************************************************************/
bool PowerOfTwoMemoryManager::Segment::isUsed(unsigned int iBlock){
	IAS_TRACER;
	if(iBlock > getSize())
		IAS_THROW(InternalException("Block number of range in PowerOfTwoMemoryManager::Segment::freeBlock."))

	return !(tBitMap[iBlock>>3] & (0x01 <<(iBlock & 0x07)));
}
/*************************************************************************/
void PowerOfTwoMemoryManager::Segment::setBucket(Byte iBucket){
	IAS_TRACER;
	if(iNumAllocated)
		IAS_THROW(InternalException("Segment has data."));

	if(iBucket > C_LgBitMapSize)
		IAS_THROW(InternalException("Bucket out of range:"));

	this->iBucket=iBucket;
}
/*************************************************************************/
const char  PowerOfTwoMemoryManager::Info::C_Tag[C_TagSize+1] = "PTMM";
/*************************************************************************/
PowerOfTwoMemoryManager::Info::Info():
		iAllocated(0),
		iWaterMark(0),
		pFreeList(0),
		pAllocatedBySizeList(0),
		iSpaceSize(0),
		iLgBaseSize(0),
		iSegments(0),
		pSegments(0),
		pSegmentList(0),
		pData(0),
		iSegmentSize(0),
		iBuckets(0),
		mutex(true){
	IAS_TRACER;
	::strncpy(sTag,C_Tag,C_TagSize);
}

/*************************************************************************/
template<class T>
static T* AssignData(void* &p,size_t& iSize, unsigned int n=1){

	T* pStart=static_cast<T*>(p);
	T* pCursor=pStart;

	size_t iDelta = reinterpret_cast<char*>(pCursor+n) - reinterpret_cast<char*>(p);

	if(iDelta > iSize)
		IAS_THROW(InternalException("Bad estimation in AssignData"));

	while(n-->0)
		new(pCursor++) T();

	iSize-=iDelta;
	p=reinterpret_cast<char*>(pCursor);
	return pStart;
}
/*************************************************************************/
void PowerOfTwoMemoryManager::Initialize(void *pStart, size_t iSize, int iLgBaseSize){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Check: "<<pStart<<", size="<<iSize);

	size_t iSizeLeft=iSize;

	if(iSize < 2*sizeof(Info))
		IAS_THROW(InternalException("Too little memory for PowerOfTwoMemoryManager."));

	Info* pInfo=AssignData<Info>(pStart,iSizeLeft);

	pInfo->iSegmentSize=1L<<(Segment::C_LgBitMapSize+iLgBaseSize);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Segment size: "<<pInfo->iSegmentSize);

	pInfo->iBuckets=Segment::C_LgBitMapSize+1;

	pInfo->iSpaceSize=iSize;
	pInfo->iLgBaseSize=iLgBaseSize;

	size_t iEstimatedNumSegments = iSize;
	iEstimatedNumSegments-=sizeof(Info);
	iEstimatedNumSegments-=sizeof(List)*(pInfo->iBuckets+1);
	iEstimatedNumSegments/=sizeof(List)+sizeof(Segment)+pInfo->iSegmentSize;

	if(iEstimatedNumSegments < pInfo->iBuckets )
		IAS_THROW(InternalException()<<"Too little memory, expected:"<<iEstimatedNumSegments<<" segments,"
		<<pInfo->iBuckets<<" buckets. Estimated memory needed: "<<(pInfo->iBuckets*(sizeof(List)+sizeof(Segment)+pInfo->iSegmentSize)));



	pInfo->pFreeList            = AssignData<List>(pStart,iSizeLeft);
	pInfo->pAllocatedBySizeList = AssignData<List>(pStart,iSizeLeft,pInfo->iBuckets);
	pInfo->pSegmentList         = AssignData<List>(pStart,iSizeLeft,iEstimatedNumSegments);
	pInfo->pSegments            = AssignData<Segment>(pStart,iSizeLeft,iEstimatedNumSegments);
	pInfo->pData                = AssignData<Byte>(pStart,iSizeLeft);

	//In case we wasted something on the data alignment.
	if(iSizeLeft + 1 < iEstimatedNumSegments * pInfo->iSegmentSize){
		iEstimatedNumSegments--;
	}

	if(iSizeLeft + 1 < iEstimatedNumSegments * pInfo->iSegmentSize)
		IAS_THROW(InternalException("Bad estimation."));

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Waisted: "<<((iSizeLeft + 1) - iEstimatedNumSegments * pInfo->iSegmentSize));

	pInfo->iSegments=iEstimatedNumSegments;

	for(int iIdx=0;iIdx<iEstimatedNumSegments;iIdx++){
		pInfo->pSegmentList[iIdx].link(pInfo->pFreeList);
	}

}
/*************************************************************************/
PowerOfTwoMemoryManager::PowerOfTwoMemoryManager(void *pStart, size_t iSize){
	IAS_TRACER;

	pInfo=(Info*)pStart;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
			Initialize(pStart,iSize);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"At: "<<pStart<<", size="<<iSize<<" at="<<(void*)this);

}
/*************************************************************************/
PowerOfTwoMemoryManager::PowerOfTwoMemoryManager(void *pStart){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pStart);

	pInfo=(Info*)pStart;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
		IAS_THROW(InternalException("PowerOfTwoMemoryManager not initialized."));

}
/*************************************************************************/
unsigned int PowerOfTwoMemoryManager::Info::getSegment(List* pList){
	IAS_TRACER;

	int iSegment=pList-pSegmentList;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"iSegment = "<<iSegment);

	if(iSegment < 0 || iSegment >= iSegments)
		IAS_THROW(InternalException("Segment number out of range."));

	return iSegment;
}

/*************************************************************************/
void *PowerOfTwoMemoryManager::Info::encodeAddress(unsigned int iSegment, unsigned int iBlock){
	IAS_TRACER;

	Byte iBucket=pSegments[iSegment].getBucket();
	Byte iLgSegSize=Segment::C_LgBitMapSize+iLgBaseSize;

	void *pResult=pData+(iBlock<<(iLgBaseSize+iBucket))+(iSegment<<iLgSegSize);
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"encodeAddress: ("<<iSegment<<","<<iBlock<<")="<<pResult);

	return pResult;
}
/*************************************************************************/
void  PowerOfTwoMemoryManager::Info::decodeAddress(const void *pAddress, unsigned int& iSegment, unsigned int& iBlock){
	IAS_TRACER;

	unsigned int iOffset=const_cast<Byte*>((const Byte*)pAddress)-pData;

	if(iOffset < 0 || iOffset > iSegments*iSegmentSize)
		IAS_THROW(InternalException("Pointer is out of data range in PowerOfTwoMemoryManager."))

	Byte iLgSegSize=Segment::C_LgBitMapSize+iLgBaseSize;
	iSegment = iOffset>>iLgSegSize;
	iBlock   = (iOffset & ((1L<<iLgSegSize) - 1))>>(pSegments[iSegment].getBucket()+iLgBaseSize);

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"decodeAddress:"<<pAddress<<"=("<<iSegment<<","<<iBlock<<")");
}
/*************************************************************************/
void* PowerOfTwoMemoryManager::Info::allocate(size_t n){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** Allocate: n="<<n<<", max size="<<iSegmentSize);

	Mutex::Locker locker(mutex, tsrMutexWaits);

	AutoTimeSample sample(tsrAllocations,LogLevel::INSTANCE.isProfile());

	if(n>iSegmentSize){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Request too much, n="<<n<<", max size="<<iSegmentSize);
		throw std::bad_alloc();
	}

	int iSize=(n-1)>>iLgBaseSize;
	int iRequestedBucket=0;
	while(iSize){
		iSize>>=1;
		iRequestedBucket++;
	}

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"ReqBucket="<<iRequestedBucket<<", size="<<(1L<<(iRequestedBucket+iLgBaseSize)));

	if(pAllocatedBySizeList[iRequestedBucket].empty()){

		if(pFreeList->empty()){
			IAS_LOG(LogLevel::INSTANCE.isError(),"Out of free segments, this="<<(void*)this);
			throw std::bad_alloc();
		}

		List *pNew = pFreeList->head();
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Added from pool: "<<getSegment(pNew));

		pNew->unlink();

		pNew->link(pAllocatedBySizeList+iRequestedBucket);
		pSegments[getSegment(pNew)].setBucket(iRequestedBucket);
	}

	unsigned int iSegment=getSegment(pAllocatedBySizeList[iRequestedBucket].head());
	unsigned int iBlock=pSegments[iSegment].allocateBlock();

	if(pSegments[iSegment].isFull()){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Segment full and will be removed");
		pAllocatedBySizeList[iRequestedBucket].head()->unlink();
	}

	if( (iAllocated+=pSegments[iSegment].getSize()) > iWaterMark)
		iWaterMark=iAllocated;

	return encodeAddress(iSegment,iBlock);
}
/*************************************************************************/
void  PowerOfTwoMemoryManager::Info::free(const void* p){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** Free: "<<p);

	Mutex::Locker locker(mutex, tsrMutexWaits);

	unsigned int iSegment;
	unsigned int iBlock;

	decodeAddress(p,iSegment,iBlock);

	if(pSegments[iSegment].isFull()){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Back on free list="<<iSegment);
		pSegmentList[iSegment].link((pAllocatedBySizeList+pSegments[iSegment].getBucket()));
	}

	pSegments[iSegment].freeBlock(iBlock);

	if(pSegments[iSegment].isEmpty()){
		pSegmentList[iSegment].unlink();
		pSegmentList[iSegment].link(pFreeList);
	}

	iAllocated-=pSegments[iSegment].getSize();

}
/*************************************************************************/
bool  PowerOfTwoMemoryManager::Info::check(const void* p){
	IAS_TRACER;

	Mutex::Locker locker(mutex, tsrMutexWaits);

	unsigned int iSegment;
	unsigned int iBlock;

	decodeAddress(p,iSegment,iBlock);

	return !pSegments[iSegment].isEmpty() && pSegments[iSegment].isUsed(iBlock);
}
/*************************************************************************/
void* PowerOfTwoMemoryManager::allocate(size_t n){
	IAS_TRACER;
	return pInfo->allocate(n);
}
/*************************************************************************/
void  PowerOfTwoMemoryManager::free(const void* p){
	IAS_TRACER;
	pInfo->free(p);
}
/*************************************************************************/
bool  PowerOfTwoMemoryManager::check(const void* p){
	IAS_TRACER;
	return pInfo->check(p);
}
/*************************************************************************/
PowerOfTwoMemoryManager::~PowerOfTwoMemoryManager()throw(){
	IAS_TRACER;
}
/*************************************************************************/
void PowerOfTwoMemoryManager::printToStream(std::ostream& os){
	IAS_TRACER;

	Mutex::Locker locker(pInfo->mutex);
	size_t iAllocatedMem=0;
	size_t iMemTotal=pInfo->iSegments*pInfo->iSegmentSize;
	int    iAllocatedCnt=0;

	int    tBucketsBlocks[64];
	int    tBucketsSegs[64];
	int    tBucketsSegsFull[64];

	bzero(tBucketsBlocks,   sizeof(int)*64);
	bzero(tBucketsSegs,     sizeof(int)*64);
	bzero(tBucketsSegsFull, sizeof(int)*64);

	int iUsedSegments=0;

	for(int iIdx=0; iIdx<pInfo->iSegments; iIdx++){

		size_t iAllocated=pInfo->pSegments[iIdx].getAllocated();
		int    iBucket=pInfo->pSegments[iIdx].getBucket();

		if(iAllocated){
			iAllocatedMem+=iAllocated*(1L<<iBucket);
			iAllocatedCnt+=iAllocated;
			tBucketsBlocks[iBucket]+=iAllocated;
			tBucketsSegs[iBucket]++;
			if(pInfo->pSegments[iIdx].isFull())
				tBucketsSegsFull[iBucket]++;
			iUsedSegments++;
		}
	}

	iAllocatedMem<<=pInfo->iLgBaseSize;

	os<<"   ---- PowerOf2MM ----   "<<std::endl;
	os<<std::endl;
	os<<"  Allocated: "<<(long)(iAllocatedMem)<<"("<<iAllocatedMem/(iMemTotal/100)<<"%) bytes of "<<iMemTotal;
	os<<" in "<<iAllocatedCnt<<" blocks, High water mark:"<<(long)(pInfo->iWaterMark)<<std::endl;
	os<<"  Allocated: "<<(long)(iUsedSegments)<<"("<<100*iUsedSegments/pInfo->iSegments<<"%) segments of "<<(long)(pInfo->iSegments)<<" total."<<std::endl;

	for(int iIdx=0; iIdx<pInfo->iBuckets; iIdx++){
		os<<" bucket "<<(1L<<(iIdx+pInfo->iLgBaseSize))<<" : "<<tBucketsBlocks[iIdx]<<"/"<<tBucketsSegs[iIdx]<<"/"<<tBucketsSegsFull[iIdx]<<std::endl;
	}

	os<<std::endl;

	os<<"  Waits:        "<<pInfo->tsrMutexWaits<<std::endl;
	os<<"  Allocations:  "<<pInfo->tsrAllocations<<std::endl;
	os<<std::endl;

	os<<"   ---- ---- ---- ----   "<<std::endl;
}
/*************************************************************************/
void PowerOfTwoMemoryManager::dump(std::ostream& os){

	IAS_TRACER;

	Mutex::Locker locker(pInfo->mutex);

	os<<"PowerOfTwoMemoryManager, entries="<<pInfo->iSegments<<std::endl;

	for(int iIdx=0; iIdx<pInfo->iSegments; iIdx++){
		os<<iIdx<<" :"<<(int)pInfo->pSegments[iIdx].getBucket()<<", "
			<<(int)pInfo->pSegments[iIdx].getAllocated()<<" / "
			<<(int)pInfo->pSegments[iIdx].getSize()<<std::endl;
	}

	for(int iIdx=0; iIdx<pInfo->iBuckets; iIdx++){
		os<<iIdx<<" ";
		pInfo->pAllocatedBySizeList[iIdx]._print(os,pInfo->pFreeList);
		os<<std::endl;
	}

	pInfo->pFreeList->_print(os,pInfo->pFreeList);
	os<<std::endl;
}
/*************************************************************************/
}

