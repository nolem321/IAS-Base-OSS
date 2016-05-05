/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/Queue.cpp
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
#include "Queue.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "MsgEntry.h"
#include "../System.h"
#include "Session.h"

#include "Subscription.h"
#include <algorithm>
#include <unistd.h>

/*************************************************************************/
/*
 * Locking:
 * 	- Single queue
 * 	- Topic first then subscribers.
 *
 */

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
/*************************************************************************/
static MsgEntry _empty;
/*************************************************************************
void Queue::Holder::set(Queue  *pQueue){

	close();
	this->pQueue=pQueue;
	pSession->registerQueue(pQueue);
}
 *************************************************************************
void Queue::Holder::close(){

	if(pQueue){
		pQueue->close();
		if(bDelete && pQueue->isType(QM_Temporary))
			 pQueue->remove();
		}

	pSession->forget(pQueue);
}
 *************************************************************************/
Queue::Queue():
	iMode(QM_NotAllocated),
	iUsageCount(0),
	pSubscription(0),
	pNextSubscriber(0),
	pPrevSubscriber(0),
	pTopic(0),
	mutex(true),
	bRemovePending(false){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Created at: "<<((void*)this));
}
/*************************************************************************/
Queue::~Queue(){
	IAS_TRACER;

	IAS_THROW(InternalException("Queue destroyed."))
}
/*************************************************************************/
Queue* Queue::open(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Opening: ["<<sName<<"]");

	Mutex::Locker locker(mutex);

	if(!isAllocatedNoLock())
		IAS_THROW(InternalException("Queue not allocated."));

	iUsageCount++;

	return this;
}
/*************************************************************************/
void Queue::close(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Closing: ["<<sName<<"]:"<<", uc="<<iUsageCount);

	Mutex::Locker locker(mutex);

	if(!isAllocatedNoLock())
			IAS_THROW(InternalException("Attempt to close queue which is not allocated !!!"));

	if(iUsageCount < 0)
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"!!!! ERROR !!!! close: ["<<sName<<"]:"<<", uc="<<iUsageCount);

	if(--iUsageCount <= 0 && bRemovePending)
		freeNoLock();
}
/*************************************************************************/
void Queue::remove(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Remove: ["<<sName<<"]:"<<", uc="<<iUsageCount);

	unsubscribe();

	Mutex::Locker locker(mutex);

	if(!isAllocatedNoLock())
			IAS_THROW(InternalException("Attempt to remove queue which is not allocated !!!"));

	setRemovePendingNoLock();

	if(iUsageCount < 0)
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"!!!! ERROR !!!! Remove: ["<<sName<<"]:"<<", uc="<<iUsageCount);

	if(iUsageCount <= 0)
		freeNoLock();
}
/*************************************************************************/
void Queue::setRemovePendingNoLock(){
	IAS_TRACER;
	bRemovePending=true;
	ptrQueueData->setRemovePending();
}
/*************************************************************************/
void Queue::setup(const String& strName, Queue::Mode iMode){
	IAS_TRACER;

	if(isAllocatedNoLock())
		IAS_THROW(InternalException("Already allocated !!!"));

	strncpy(this->sName,strName.c_str(),C_MaxQNameLength);
	sName[C_MaxQNameLength]=0;

	QS::SHM::QueueAllocator<MsgEntry> allocator;

	this->iMode=iMode;
	this->iUsageCount=0;
	this->pTopic=0;
	this->pNextSubscriber=this->pPrevSubscriber=0;

	this->pSubscription=0;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Allocated: ["<<sName<<"]:"<<":"<<iMode<<", a="<<(void*)this);
}
/*************************************************************************/
void Queue::setupQueue(const String& strName, int iQueueSize){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	setup(strName,QM_Queue);
	ptrQueueData=QueueData::Create(iQueueSize);
}
/*************************************************************************/
void Queue::setupLink(const String& strName, Queue* pTarget){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	setup(strName,QM_Queue);
	ptrQueueData=pTarget->ptrQueueData;

}
/*************************************************************************/
void Queue::setupTopic(const String& strName, int iQueueSize){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
	setup(strName,QM_Topic);
	ptrQueueData=QueueData::Create(iQueueSize);
	this->pNextSubscriber=this->pPrevSubscriber=this;
}
/*************************************************************************/
void Queue::setupTemporary(int iQueueSize){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	timespec ts;
	clock_gettime(CLOCK_MONOTONIC,&ts);
	StringStream ssName;
	ssName<<".tmp."<<getpid()<<ts.tv_sec<<ts.tv_nsec;

	setup(ssName.str(),QM_Temporary);
	ptrQueueData=QueueData::Create(iQueueSize);

}
/*************************************************************************/
void Queue::freeNoLock(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Free: ["<<sName<<"]:"<<iUsageCount<<":"<<iMode);
	/*
	 * Remove content references.
	 */

	ptrQueueData=0;

	if(pSubscription){
		QS::SHM::QueueAllocator<Subscription>::Free(pSubscription);
		pSubscription=0;
	}

	iMode=QM_NotAllocated;
	bRemovePending=false;

	if(iMode == QM_Topic)
		removeSubscribersNoLock();

}
/*************************************************************************/
bool Queue::put(const MsgEntry& refMsgEntry, unsigned int iWaitTimeMs){
	IAS_TRACER;

	/*
	 * No Locks here, ptrContent modifications will wait anyway
	 * and we do not care for other changes
	 */

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"PUT: "<<sName);

	return ptrQueueData->put(refMsgEntry,iWaitTimeMs);
}
/*************************************************************************/
bool Queue::get(MsgEntry& refMsgEntry, unsigned int iWaitTimeMs){
	IAS_TRACER;

	/*
	 * No Locks here, ptrContent modifications will wait anyway
	 * and we do not care for other changes
	 */

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"GET: "<<sName);

	return ptrQueueData->get(refMsgEntry,iWaitTimeMs);
}
/*************************************************************************/
bool Queue::browse(MsgEntry& refMsgEntry, BrowseLocator& iLocation, unsigned int iWaitTimeMs){
	IAS_TRACER;

	/*
	 * No Locks here, ptrContent modifications will wait anyway
	 * and we do not care for other changes
	 */

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"BROWSE: "<<sName);

	return ptrQueueData->browse(refMsgEntry,iLocation,iWaitTimeMs);
}
/*************************************************************************/

void Queue::subscribe(Queue *pTopic, Subscription* pSubscription){
	IAS_TRACER;

	Mutex::Locker locker1(pTopic->mutex);

	if(pTopic->iMode != QM_Topic)
		IAS_THROW(InternalException("//TODO: is not a topic !"));

	Mutex::Locker locker2(mutex);

	if(bRemovePending)
		IAS_THROW(InternalException("//TODO: Queue about to be closed !"));

	if(iMode != QM_Queue && iMode != QM_Temporary)
			IAS_THROW(InternalException("Bad queue mode."));

	if(pSubscription || pNextSubscriber || pPrevSubscriber || this->pTopic){
		IAS_THROW(InternalException(String("Already subscribed:")+sName+ (pTopic ? pTopic->sName : " ? ")));
	}

	pTopic->addSubscriberNoLock(this);
	this->pSubscription=pSubscription;             	//TODO auto remove ?
}
/*************************************************************************/
void Queue::addSubscriberNoLock(Queue *pSubcriberQueue){
	IAS_TRACER;

	if(iMode != QM_Topic)
		IAS_THROW(InternalException(String("//TODO Bad queue mode, not a topic:")+sName));

	if(bRemovePending)
		IAS_THROW(InternalException("//TODO: Queue about to be closed !"));

	pNextSubscriber->pPrevSubscriber=pSubcriberQueue;

	pSubcriberQueue->pNextSubscriber=pNextSubscriber;
	pSubcriberQueue->pPrevSubscriber=this;

	pNextSubscriber=pSubcriberQueue;

	pSubcriberQueue->pTopic=this;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Subscriber added: "<<sName<<", sub="<<pSubcriberQueue->sName);
}
/*************************************************************************/
void Queue::unsubscribe(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"remove: "<<(void*)this);

	Queue *pTopic;
	{
		Mutex::Locker locker(mutex);
		pTopic=this->pTopic;
	}

	if(!pTopic){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"No subscription found for: "<<sName);
		return;
	}

	Mutex::Locker locker1(pTopic->mutex);
	Mutex::Locker locker(mutex);

	if(pTopic != this->pTopic)             //Check for the race.
		return;

	unsubscribeNoLock();

}
/*************************************************************************/
void Queue::unsubscribeNoLock(){
	IAS_TRACER;

	if(!pNextSubscriber || !pPrevSubscriber)
		IAS_THROW(InternalException(String("//TODO Inconsistent state: ")+sName+" : "+__FUNCTION__));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"remove: "<<(void*)this<<":"<<(void*)pPrevSubscriber<<":"<<(void*)pNextSubscriber);

	pNextSubscriber->pPrevSubscriber=pPrevSubscriber;
	pPrevSubscriber->pNextSubscriber=pNextSubscriber;

	if(pSubscription){
		QS::SHM::QueueAllocator<Subscription>::Free(pSubscription);
		pSubscription=0;
	}

	pTopic=0;
	this->pNextSubscriber=this->pPrevSubscriber=0;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"done: "<<(void*)this<<":"<<(void*)pPrevSubscriber<<":"<<(void*)pNextSubscriber);

}
/*************************************************************************/
void Queue::removeSubscribersNoLock(){
	IAS_TRACER;

	if(!pNextSubscriber)
		return;

	if(iMode != QM_Topic)
		IAS_THROW(InternalException("Not a topic."));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"info: "<<(void*)this<<", next="<<(void*)pNextSubscriber);

	while(pNextSubscriber != this){
		Mutex::Locker locker(pNextSubscriber->mutex);
		//This is tricky, unsubscribeNoLock() will advance pNextSubcriber=pNextSubscriber->pNextSubscriber;
		pNextSubscriber->unsubscribeNoLock();
	}
}
/*************************************************************************/
void Queue::getAndPublish(unsigned int iWaitTimeMs){
	IAS_TRACER;

	MsgEntry entry;

	if(get(entry,iWaitTimeMs)){

		Mutex::Locker locker(mutex);
		Queue *pCursor=pNextSubscriber;

		while(pCursor != this){

			//Mutex::Locker locker(pCursor->mutex);
			//It is not needed as we have a lock on whole topic

			pCursor->put(entry);
			pCursor=pCursor->pNextSubscriber;
		}
	}
}
/*************************************************************************/

}
}
}
}
