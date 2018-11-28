/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/QueueTable.cpp
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
#include "QueueTable.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Session.h"
#include "JournalObjectEntry.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
/*************************************************************************/
QueueTable::QueueTable(size_t iSize):
	iSize(iSize),
	mutex(true),
	iTopicInfoVersion(0),
	iDftQueueSize(100){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Created at: "<<((void*)this)<<", size="<<iSize);

	QS::SHM::SystemAllocator<Queue> allocator;

	tabQueues = new(allocator.allocate(iSize))Queue[iSize];

}
/*************************************************************************/
QueueTable::~QueueTable(){
	IAS_TRACER;

	//IAS_THROW(InternalException("QueueTable destroyed."))
}
/*************************************************************************/
Queue* QueueTable::createTemporary(const String& strBasename){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	int iIdx=0;

	while(iIdx<iSize && tabQueues[iIdx].isAllocated())
		iIdx++;

	if(iIdx == iSize)
		IAS_THROW(InternalException("Out of resources, no queue slots."));

	tabQueues[iIdx].setupTemporary(strBasename, iDftQueueSize);

	return tabQueues+iIdx;
}
//TODO Use prime numbers for size and hashing
//TODO lookup should open queue otherwise the race is possible.
/*************************************************************************/
Queue* QueueTable::open(const String& strQName){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Find: ["<<strQName<<"]");

	Mutex::Locker  locker(mutex);

	AutoTimeSample as(tsrLookups);

	Queue *pQueue=lookupNoLock(strQName);

	return pQueue->open();
}
/*************************************************************************/
Queue* QueueTable::lookup(const String& strQName){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Find: ["<<strQName<<"]");

	Mutex::Locker  locker(mutex);

	AutoTimeSample as(tsrLookups);

	Queue *pQueue=lookupNoLock(strQName);

	return pQueue;
}
/*************************************************************************/
Queue* QueueTable::lookupNoLock(const String& strQName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Find: ["<<strQName<<"]");

	//TODO faster search, eg. will hash names.

	int iIdx=0;

	while(iIdx<iSize &&
		  (!tabQueues[iIdx].isAllocated() ||
		   strQName.compare(tabQueues[iIdx].getName()) != 0))
		iIdx++;

	if(iIdx == iSize)
		IAS_THROW(ItemNotFoundException(String(strQName)));


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"At: "<<iIdx);
	return tabQueues+iIdx;
}

/*************************************************************************/
Queue* QueueTable::createQueue(const String& strQName, int iSize){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Create: ["<<strQName<<"]");
	Mutex::Locker  locker(mutex);
	Queue *pResult = findFreeSlot(strQName);
	pResult->setupQueue(strQName,iSize != C_DftQueueSize ? iSize : iDftQueueSize);
	return pResult;
}
/*************************************************************************/
Queue*  QueueTable::createLink(const String& strName, const String& strTargetName){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Create: ["<<strName<<"] => ["<<strTargetName<<"]");
	Mutex::Locker  locker(mutex);
	Queue *pResult = findFreeSlot(strName);
	Queue *pTarget =  lookupNoLock(strTargetName);
	pResult->setupLink(strName,pTarget);
	return pResult;
}
/*************************************************************************/
Queue*  QueueTable::createTopic(const String& strQName, int iSize){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Create: ["<<strQName<<"]");
	Mutex::Locker  locker(mutex);

	Queue *pResult = findFreeSlot(strQName);
	pResult->setupTopic(strQName,iSize != C_DftQueueSize ? iSize : iDftQueueSize);
	iTopicInfoVersion++;

	return pResult;
}
/*************************************************************************/
/* Check the whole table for duplicate names, too.
 *
 */
Queue* QueueTable::findFreeSlot(const String& strQName){

	IAS_TRACER;

	int iEmptyIdx=-1;

	for(int iIdx=0; iIdx<iSize;iIdx++){

		  if(tabQueues[iIdx].isAllocated()){
			if(strQName.compare(tabQueues[iIdx].getName()) == 0)
			  IAS_THROW(InternalException(String(strQName)+=" already exists."));
		  }else{
			  if(! tabQueues[iIdx].isAllocated())
				  iEmptyIdx=iIdx;
		  }
	}

	if(iEmptyIdx < 0)
		IAS_THROW(InternalException("Out of resources, no queue slots."));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"At: "<<iEmptyIdx);

	return tabQueues+iEmptyIdx;
}
/*************************************************************************/
void QueueTable::deleteQueue(const String& strQName){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	Queue *pQueue = lookupNoLock(strQName);
	pQueue->remove();

}
/*************************************************************************/
void QueueTable::deleteTopic(const String& strQName){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	Queue *pQueue = lookupNoLock(strQName);
	pQueue->remove();

	iTopicInfoVersion++;
}
/*************************************************************************/
void QueueTable::setDftQueueSize(int iDftQueueSize){
	IAS_TRACER;
	this->iDftQueueSize=iDftQueueSize;
}
/*************************************************************************/
}
}
}
}
