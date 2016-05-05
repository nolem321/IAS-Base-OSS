/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/ContentStorage.cpp
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
#include "ContentStorage.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/Attachment.h>
#include <qs/Impl/shm/Content.h>


namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {


/*************************************************************************/
ContentStorage::Descriptor::Descriptor(ContentStorage::Entry* pEntry):pEntry(pEntry){
	IAS_TRACER;
	if(this->pEntry)
		this->pEntry->incUsageCount();
}
/*************************************************************************/
ContentStorage::Descriptor::Descriptor(const Descriptor& other):pEntry(other.pEntry){
	IAS_TRACER;
	if(pEntry)
		pEntry->incUsageCount();
}
/*************************************************************************/
ContentStorage::Descriptor::~Descriptor(){
	IAS_TRACER;
	if(pEntry)
		pEntry->decUsageCount();
}
/*************************************************************************/
ContentStorage::Descriptor& ContentStorage::Descriptor::operator=(const Descriptor& other){
	IAS_TRACER;

	if(pEntry)
		pEntry->decUsageCount();

	pEntry=other.pEntry;

	if(pEntry)
		pEntry->incUsageCount();

	return *this;
}
/*************************************************************************/
ContentStorage::Entry* ContentStorage::Descriptor::getEntry(){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pEntry);
	return pEntry;
}
/*************************************************************************/
ContentStorage::Entry::Entry():
		iUsageCount(0),
		pMemorySlot(0),
		mutex(true),
		bUsed(false){}
/*************************************************************************/
void ContentStorage::Entry::incUsageCount(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	iUsageCount++;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," ++Ref "<<((void*)this)<<", iUsageCount="<<(iUsageCount));
}
/*************************************************************************/
int ContentStorage::Entry::decUsageCount(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," --Ref "<<((void*)this)<<", iUsageCount="<<(iUsageCount-1));
	if(--iUsageCount == 0){
		QS::SHM::Content::Destroy(this);
		bUsed=false;
	}
	return iUsageCount;
}
/*************************************************************************/
int  ContentStorage::Entry::getUsageCount(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	return iUsageCount;
}
/*************************************************************************/
ContentStorage::ContentStorage(int iMaxEntries):
		iMaxEntries(iMaxEntries),
		iNumErrors(0),
		tabEntries(0),
		mutex(true){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Created at: "<<((void*)this)<<", iMaxEntries="<<this->iMaxEntries);

	QS::SHM::QueueAllocator<Entry> allocator;
	tabEntries = new(allocator.allocate(iMaxEntries))Entry[iMaxEntries];

}
/*************************************************************************/
ContentStorage::~ContentStorage() throw(){
	IAS_TRACER;

	IAS_THROW(InternalException("ContentStorage destroyed."))
}
/*************************************************************************/
ContentStorage::Descriptor ContentStorage::allocateNew(){
	IAS_TRACER;

	Mutex::Locker locker(mutex,tsrMutexWaits);
	AutoTimeSample ts(tsrAllocations);

	//TODO faster search and do not lock all !!

	int iIdx=0;
	int iStart=rand() % iMaxEntries;
	while(tabEntries[(iIdx+iStart)%iMaxEntries].bUsed && iIdx<iMaxEntries)
		iIdx++;

	if(iIdx >= iMaxEntries){
		iNumErrors++;
		IAS_THROW(InternalException("Out of resources: no Entries in the content store."));
	}
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Allocated: "<<(iIdx+iStart)%iMaxEntries<<", entry="<<(void*)(tabEntries+iIdx));

	tabEntries[(iIdx+iStart)%iMaxEntries].bUsed=true;

	return Descriptor(tabEntries+((iIdx+iStart)%iMaxEntries));
}
/*************************************************************************/
void ContentStorage::dump(std::ostream& os){

	Mutex::Locker locker(mutex);

	int iIdx=0;

	int iAllocated=0;
	while(iIdx<iMaxEntries){

		Mutex::Locker locker(tabEntries[iIdx].mutex);

		if(tabEntries[iIdx].bUsed)
			iAllocated++;

		if(tabEntries[iIdx].iUsageCount > 0 && iIdx < 10){
			//os<<iIdx<<":"<<tabEntries[iIdx].iUsageCount;
			//os<<":"<<(void*)tabEntries[iIdx].pMemorySlot;
			//os<<std::endl;
		}

		iIdx++;
	}

	os<<" Used:   "<<iAllocated<<" ( "<<100*iAllocated/iMaxEntries;
	os<<"% ) of "<<iMaxEntries<<". Errors:       "<<iNumErrors<<std::endl;
	os<<" Waits:        "<<tsrMutexWaits<<std::endl;
	os<<" Allocations:  "<<tsrAllocations<<std::endl;

}
/*************************************************************************/
}
}
}
}
