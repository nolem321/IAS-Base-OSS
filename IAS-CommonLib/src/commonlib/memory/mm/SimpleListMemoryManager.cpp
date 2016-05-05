/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/SimpleListMemoryManager.cpp
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
#include "SimpleListMemoryManager.h"
#include "commonlib/exception/InternalException.h"

#include <commonlib/commonlib.h>
#include <new>
#include <string.h>
#include <strings.h>

namespace IAS {

/*************************************************************************/
const char  SimpleListMemoryManager::Info::C_Tag[C_TagSize+1] = "SLMM";
/*************************************************************************/
SimpleListMemoryManager::Info::Info():
		iNumEntries(0),
		iAllocated(0),
		iWaterMark(0),
		last(0),
		tail(0),
		head(0),
		iSpaceSize(0),
		mutex(false){
	IAS_TRACER;
	::strncpy(sTag,C_Tag,C_TagSize);
}
/*************************************************************************/
void SimpleListMemoryManager::Initialize(void *pStart, size_t iSize){
	IAS_TRACER;

	if(iSize < 16*sizeof(Entry) +  2*sizeof(Info) )
			IAS_THROW(InternalException("Too little memory."));


	Info*       pInfo=(Info*)pStart;
	Entry*      tabEntries=(Entry*)(pInfo+1);

	new(pInfo)Info();

	pInfo->iSpaceSize=iSize;
	iSize-=sizeof(Info);

	pInfo->iNumEntries=iSize / sizeof(Entry) - 2;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Num entries: "<<pInfo->iNumEntries<<" at: "<<pStart<<", size="<<iSize);

	pInfo->last=pInfo->head=tabEntries;
	pInfo->tail=tabEntries+pInfo->iNumEntries + 1;

	pInfo->head->iSize=pInfo->iNumEntries;
	pInfo->head->next=pInfo->tail;
	pInfo->head->prev=pInfo->tail;

	pInfo->tail->iSize=-1;
	pInfo->tail->next=pInfo->head;
	pInfo->tail->prev=pInfo->head;

}
/*************************************************************************/
SimpleListMemoryManager::SimpleListMemoryManager(void *pStart, size_t iSize){
	IAS_TRACER;

	pInfo=(Info*)pStart;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
			Initialize(pStart,iSize);

	tabEntries=(Entry*)(pInfo+1);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Num entries: "<<pInfo->iNumEntries<<" at: "<<pStart<<", size="<<iSize<<" at="<<(void*)this);

}
/*************************************************************************/
SimpleListMemoryManager::SimpleListMemoryManager(void *pStart){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pStart);

	pInfo=(Info*)pStart;

	if(strncmp(pInfo->sTag,Info::C_Tag,Info::C_TagSize) != 0)
		IAS_THROW(InternalException("SimpleListMemoryManager not initialized."));

	tabEntries=(Entry*)(pInfo+1);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Num entries: "<<pInfo->iNumEntries<<" at: "<<pStart<<", size="<<pInfo->iSpaceSize);

	if(LogLevel::INSTANCE.isInfo())
		dump(std::cerr);

}
/*************************************************************************/
void* SimpleListMemoryManager::allocate(size_t n){

	Mutex::Locker locker(pInfo->mutex, pInfo->tsrMutexWaits);

	AutoTimeSample sample(pInfo->tsrAllocations,LogLevel::INSTANCE.isProfile());

	int iSearches=0;

	Entry* current=pInfo->last;
	EntryIndex iEntries = (n+sizeof(Entry)-1) / sizeof(Entry);

	bool bStop=false;

	while(!bStop){
		iSearches++;
	  if(current->isFree() && current->iSize > iEntries){
		  bStop=true;
	  }else	if(current->isFree() && current->next->isFree()){

			if(current->next == pInfo->last)
				pInfo->last=current->next->next;

			current->iSize+=current->next->iSize+1;
			current->next->next->prev=current;
			current->next=current->next->next;

		}else{
			current=current->next;
			bStop = current == pInfo->last;
		}

	}

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Got: "<<(current-tabEntries));


	if(!current->isFree() || current->iSize < iEntries){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Cannot allocate: "<<n<<" in allocator at: "<<(void*)pInfo<<"free = "<<current->isFree()
				<<", s/e = "<<current->iSize<<" of "<<iEntries);
		if(LogLevel::INSTANCE.isDetailedInfo())
			dump(std::cerr);
		if(LogLevel::INSTANCE.isExceptionThrow())
			IAS_MY_STACK().printStack(std::cerr);
		throw std::bad_alloc();
	}

	if( current->iSize <= iEntries + FAST_ALLOC ){
		current->allocate();
		pInfo->last=current->next;

		pInfo->iAllocated+=current->getSize();
		if(pInfo->iWaterMark < pInfo->iAllocated)
			pInfo->iWaterMark=pInfo->iAllocated;

		pInfo->tsrSearchesNoSplit.addSample(iSearches);
		return (void*)(current+1) ;
	}

	Entry* split = current + iEntries + 1;

	split->iSize=current->iSize - (iEntries + 1);
	current->iSize=iEntries;

	split->next=current->next;
	split->next->prev=split;
	split->prev=current;
	current->next=split;

	current->allocate();
	pInfo->last=split;

	pInfo->iAllocated+=current->getSize();
	if(pInfo->iWaterMark < pInfo->iAllocated)
		pInfo->iWaterMark=pInfo->iAllocated;

	pInfo->tsrSearches.addSample(iSearches);
	return (void*)(current+1);
}
/*************************************************************************/
void  SimpleListMemoryManager::free(const void* p){


	Entry* returned = (Entry*)p;
	returned--;
	//check((void*)returned);

	Mutex::Locker locker(pInfo->mutex, pInfo->tsrMutexWaits);


	if(returned->isFree()){
		IAS_MY_STACK().printStack(std::cerr);
		IAS_THROW(InternalException("Entry is not allocated!"));
	}

	returned->free();

	pInfo->iAllocated-=returned->getSize();

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Return: "<<(void*)this<<", e="<<(returned-tabEntries)<<" "<<pInfo->iAllocated);

	pInfo->last = returned;
}
/*************************************************************************/
bool  SimpleListMemoryManager::check(const void* p){

	Mutex::Locker locker(pInfo->mutex, pInfo->tsrMutexWaits);

	Entry* returned = (Entry*)p;
	returned--;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"Check: "<<(returned-tabEntries));

	for(Entry* cursor=pInfo->head;
		cursor !=pInfo->tail;
		cursor=cursor->next)
		if(cursor == returned)
			return true;


	IAS_LOG(LogLevel::INSTANCE.isError(),"This is not my pointer: "<<p<<", this= "<<(void*)this);
	IAS_MY_STACK().printStack(std::cerr);
	//IAS_THROW(InternalException("This is not my pointer!"));
	//dump(std::cerr);
	return false;
}
/*************************************************************************/
SimpleListMemoryManager::~SimpleListMemoryManager()throw(){
	IAS_TRACER;
}
/*************************************************************************/
static inline int _backetNo(long iSize, int iMax){
	int iResult=0;
	iSize>>=6;
	while(iSize || iResult >= iMax){
		iSize>>=1;
		iResult++;
	}
	return iResult;
}
/*************************************************************************/
void SimpleListMemoryManager::printToStream(std::ostream& os){

	Mutex::Locker locker(pInfo->mutex);
	
	long tFreeBuckets[32];
	bzero(tFreeBuckets,sizeof(long)*32);

	long tFreeContinous[32];
	bzero(tFreeContinous,sizeof(long)*32);

	long tAllocBuckets[32];
	bzero(tAllocBuckets,sizeof(long)*32);

	long iFreeBuckets=0;
	long iFreeContinous=0;
	long iAllocBuckets=0;

	long iFreeTotal=0;
	long iAllocTotal=0;

	os<<std::endl;
	os<<"SimpleListMemoryManager, entries="<<pInfo->iNumEntries<<", bucket size="<<sizeof(Entry)<<" bytes."<<std::endl;
	os<<"Distribution (free /continuous free / allocated):"<<std::endl;
	long iContinous=0;
	for(Entry* current=pInfo->head;
			current->next!=pInfo->head;
			current=current->next){
		if(current->isFree()){
			iContinous+=current->getSize();
			iFreeTotal+=current->getSize();
			tFreeBuckets[_backetNo(current->iSize,32)]++;
			iFreeBuckets++;

		}else{
			tAllocBuckets[_backetNo(-(current->iSize),32)]++;
			if(iContinous)
				tFreeContinous[_backetNo(iContinous,32)]++;
			iAllocTotal+=current->getSize();
			iAllocBuckets++;
			iFreeBuckets++;
			iContinous=0;
		}
	}

	for(int i=0;(1L<<(i+5))<=(iAllocTotal+iFreeTotal);i++)
		os<<" less than "<<(1L<<(i+6))<<" : "<<tFreeBuckets[i]<<" / "<<tFreeContinous[i]<<" / "<<tAllocBuckets[i]<<std::endl;

	os<<"Totals: ";

	os.width(10);

	os<<(long)iAllocTotal*sizeof(Entry)<<" ("<<(long)(100*iAllocTotal/(iAllocTotal+iFreeTotal))
			<<"%) bytes allocated of "<<sizeof(Entry)*(iAllocTotal+iFreeTotal)<<" total bytes. Fragmentation: "<<(long)(100*iFreeContinous/iFreeBuckets)<<"%"<<std::endl;

	os<<"Allocated: "<<(long)(pInfo->iAllocated)*sizeof(Entry)<<", High water mark:"<<(long)(pInfo->iWaterMark)*sizeof(Entry)<<std::endl;
	os<<"  Waits:        "<<pInfo->tsrMutexWaits<<std::endl;
	os<<"  Allocations:  "<<pInfo->tsrAllocations<<std::endl;
	os<<"  Searches:     "<<pInfo->tsrSearches<<std::endl;
	os<<"  Searches (F): "<<pInfo->tsrSearchesNoSplit<<std::endl;
	os<<std::endl;
}
/*************************************************************************/
void SimpleListMemoryManager::dump(std::ostream& os){

	os<<"SimpleListMemoryManager, entries="<<pInfo->iNumEntries<<std::endl;

	for(Entry* current=pInfo->head; current->next!=pInfo->head; current=current->next){
		os<<(current->isFree() ? 'F' : 'A')<<"["<<(current-tabEntries)<<","<<(current->next-tabEntries)<<"]="<<abs(current->iSize)<<std::endl;
	}
}
/*************************************************************************/
}
