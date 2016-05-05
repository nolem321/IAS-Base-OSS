/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/QueueData.cpp
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
#include "QueueData.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "MsgEntry.h"
#include "../Attachment.h"

#include "Subscription.h"
#include <algorithm>

/*************************************************************************/
/*
 * Locking:
 * 	- Single queue
 * 	- Topic first then subscribers.
 *
 */

//TODO signal handling for get waits !!!
//TODO rollback/session queue cleanup !!!

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

/*************************************************************************/
void QueueData::Stats::reset(QueueDataSize iMaxNumMsgs){

	this->tsrBrowse.reset();
	this->tsrGet.reset();
	this->tsrPut.reset();
	this->tsrMutexWait.reset();
	this->iMaxNumMsgs=iMaxNumMsgs;

}
/*************************************************************************/
void QueueData::Holder::assign(QueueData   *pQueueData){
	IAS_TRACER;
	dispose();

	if(pQueueData){
		Mutex::Locker locker(pQueueData->mutex);
		pQueueData->iRefCount++;
	}

	this->pQueueData=pQueueData;
}
/*************************************************************************/
void QueueData::Holder::dispose(){
	IAS_TRACER;

	if(!pQueueData)
		return;

	bool bDelete;

	{
		Mutex::Locker locker(pQueueData->mutex);
		bDelete=pQueueData->iRefCount == 0;
	}

	if(bDelete)
		QS::SHM::QueueAllocator<QueueData>::Free(pQueueData);
}
/*************************************************************************/
static MsgEntry _empty;
/*************************************************************************/
QueueData* QueueData::Create(QueueData::QueueDataSize iSize){
	IAS_TRACER;

	QS::SHM::QueueAllocator<QueueData>::PtrHolder ptrNew;
	ptrNew=QS::SHM::QueueAllocator<QueueData>::Create();
	ptrNew->setup(iSize);

	return ptrNew.pass();
}
/*************************************************************************/
QueueData::QueueData():
	iQueueDataSize(0),
	iRefCount(0),
	iNumMsgs(0),
	iHead(0),
	tabEntries(0),
	mutex(true),
	cndReader(true),
	cndWriter(true),
	bRemovePending(false),
	bOverwriteOnQFull(true){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Created at: "<<((void*)this));
}
/*************************************************************************/
QueueData::~QueueData(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Destroyed at: "<<((void*)this));

	/*
	 * Remove content references.
	 */

	if(tabEntries){

		while(iNumMsgs--){
			tabEntries[ iHead ] = _empty;
			iHead = ++iHead % iQueueDataSize;
		}

		QS::SHM::QueueAllocator<MsgEntry> allocator;
		allocator.deallocate(tabEntries,this->iQueueDataSize);
		tabEntries=0;
	}

}
/*************************************************************************/
void QueueData::setRemovePending(){
	IAS_TRACER;

	if(--iRefCount == 0){
		bRemovePending=true;
		cndReader.broadcast();
		cndWriter.broadcast();
	}
}
/*************************************************************************/
void QueueData::setup(QueueDataSize iQueueDataSize){
	IAS_TRACER;

	if(tabEntries)
		IAS_THROW(InternalException("Entries not freed !!!"));

	QS::SHM::QueueAllocator<MsgEntry> allocator;

	this->iQueueDataSize=iQueueDataSize;
	this->iRefCount=0;
	this->iHead=0;
	this->iNumMsgs=0;

	tabEntries = new(allocator.allocate(iQueueDataSize))MsgEntry[iQueueDataSize];

	memset(const_cast<Stats*>(&stats),0,sizeof(Stats));
}
/*
 * TODO optimize  Timed Condition Wait - recompute
 *
       The pthread_cond_timedwait() function allows an application to give up waiting for a particular condition after a given amount of time. An example of its use  fol-
       lows:

              (void) pthread_mutex_lock(&t.mn);
                      t.waiters++;
                  clock_gettime(CLOCK_REALTIME, &ts);
                  ts.tv_sec += 5;
                  rc = 0;
                  while (! mypredicate(&t) && rc == 0)
                      rc = pthread_cond_timedwait(&t.cond, &t.mn, &ts);
                  t.waiters--;
                  if (rc == 0) setmystate(&t);
              (void) pthread_mutex_unlock(&t.mn);

       By  making  the timeout parameter absolute, it does not need to be recomputed each time the program checks its blocking predicate.  If the timeout was relative, it
       would have to be recomputed before each call. This would be especially difficult since such code would need to take into account the possibility of  extra  wakeups
       that result from extra broadcasts or signals on the condition variable that occur before either the predicate is true or the timeout is due.

 *
 */
/*************************************************************************/
bool QueueData::put(const MsgEntry& refMsgEntry, unsigned int iWaitTimeMs){
	IAS_TRACER;

	Mutex::Locker locker(mutex,stats.tsrMutexWait);

	if(bRemovePending)
		IAS_THROW(InternalException("//TODO: QueueData about to be removed !"));


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"P>: ["<<(void*)this<<"]    "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	unsigned int iStartTime = TypeTools::GetTimeMS();

	while(iNumMsgs >= iQueueDataSize){

		if(bOverwriteOnQFull){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," Overwrite: "<<(void*)this);
			iHead = ++iHead % iQueueDataSize;
			iNumMsgs--;
		}else{

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," Waits (cancel): "<<(void*)this);

			{
					Thread::Cancellation tc(true);

					if(!mutex.wait(cndWriter,iWaitTimeMs))
						return false;
			}

			iWaitTimeMs-=TypeTools::GetTimeMS()-iStartTime;


			if(bRemovePending)
				IAS_THROW(InternalException("//TODO: QueueData about to be removed !"));

		};

	}/* WHILE: queue is full. */

	AutoTimeSample sample(stats.tsrPut);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"       <P2 "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	tabEntries[ (iHead+iNumMsgs) % iQueueDataSize ]=refMsgEntry;
	iNumMsgs++;
	if(iNumMsgs > stats.iMaxNumMsgs)
		stats.iMaxNumMsgs=iNumMsgs;


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"       <P3 "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	cndReader.broadcast();

	return true;
}
/*************************************************************************/
bool QueueData::get(MsgEntry& refMsgEntry, unsigned int iWaitTimeMs){
	IAS_TRACER;

	Mutex::Locker locker(mutex, stats.tsrMutexWait);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"<G: ["<<(void*)this<<"]    "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	if(bRemovePending)
		IAS_THROW(InternalException("//TODO: QueueData about to be closed : "));

	unsigned int iStartTime = TypeTools::GetTimeMS();

	while(iNumMsgs == 0){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," Waits: "<<(void*)this<<", iStartTime="<<iStartTime<<", iWaitTime="<<iWaitTimeMs);

		{
				Thread::Cancellation tc(true);

				if(!mutex.wait(cndReader,iWaitTimeMs))
					return false;
		}


		iWaitTimeMs-=TypeTools::GetTimeMS()-iStartTime;


		if(bRemovePending)
			IAS_THROW(InternalException("//TODO: QueueData about to be closed !"));

	}

	AutoTimeSample sample(stats.tsrGet);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"       <G2 "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	refMsgEntry = tabEntries[ iHead ];
	tabEntries[ iHead ] = _empty;
	iHead = ++iHead % iQueueDataSize;
	iNumMsgs--;

	cndWriter.broadcast();

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"       <G3 "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize);

	return true;
}
/*************************************************************************/
bool QueueData::browse(MsgEntry& refMsgEntry, BrowseLocator& iLocation, unsigned int iWaitTimeMs){
	IAS_TRACER;

	Mutex::Locker locker(mutex, stats.tsrMutexWait);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"<B: ["<<(void*)this<<"]    "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize<<", Loc="<<iLocation);

	if(bRemovePending)
		IAS_THROW(InternalException("//TODO: QueueData about to be closed : "));

	unsigned int iStartTime = TypeTools::GetTimeMS();

	if(iQueueDataSize == 1 && iLocation != C_StartLocation)
		return false;

	bool bFirst=false;

	if(iLocation == C_StartLocation){
		iLocation=iHead;
		bFirst=true;
	}

	while(iNumMsgs &&
			!tabEntries[iLocation] &&
			(iLocation != (iHead + iNumMsgs) % iQueueDataSize || iQueueDataSize == 1) )
		iLocation = ++iLocation % iQueueDataSize;

	while(!iNumMsgs ||
		  (iLocation == (iHead + iNumMsgs) % iQueueDataSize && iQueueDataSize > 1 && !bFirst) ){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," Waits: "<<(void*)this<<", iStartTime="<<iStartTime<<", iWaitTime="<<iWaitTimeMs);

		if(!mutex.wait(cndReader,iWaitTimeMs))
			return false;

		iWaitTimeMs-=TypeTools::GetTimeMS()-iStartTime;


		if(bRemovePending)
			IAS_THROW(InternalException("//TODO: QueueData about to be closed !"));

	}

	while(!tabEntries[iLocation])
		iLocation = ++iLocation % iQueueDataSize;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"  B2: ["<<(void*)this<<"]    "<<iHead<<", "<<iNumMsgs<<" / "<<iQueueDataSize<<", Loc="<<iLocation);

	AutoTimeSample sample(stats.tsrBrowse);
	refMsgEntry = tabEntries[ iLocation ];
	iLocation = ++iLocation % iQueueDataSize;

	return true;
}

/*************************************************************************/

}
}
}
}
