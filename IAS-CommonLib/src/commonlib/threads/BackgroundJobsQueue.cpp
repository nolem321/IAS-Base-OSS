/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobsQueue.cpp
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
#include "BackgroundJobsQueue.h"

#include <commonlib/commonlib.h>
#include "BackgroundJobEntry.h"

namespace IAS {

/*************************************************************************/
BackgroundJobsQueue::BackgroundJobsQueue(int iQueueSize):
		iQueueSize(iQueueSize),
		iNumEntries(0),
		bClosed(false){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "QS="<<iQueueSize);
}

/*************************************************************************/
BackgroundJobsQueue::~BackgroundJobsQueue() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void BackgroundJobsQueue::addEntry(BackgroundJobEntry *pEntry){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);

	if(iNumEntries >= iQueueSize)
		IAS_THROW(IAS::InternalException("iNumEntries >= iQueueSize"));

	IAS_CHECK_IF_VALID(pEntry);
	phcJobEntries.addPointer(pEntry);
	iNumEntries++;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "iNumEntries="<<iNumEntries);
	theConditionEmpty.signal();
}

/*************************************************************************/
BackgroundJobEntry *BackgroundJobsQueue::assignEntry(BackgroundJobThread *pThread){
	IAS_TRACER;

	Mutex::Locker aLocker(theLock);

	BackgroundJobEntry *pResult = NULL;

	do{

		IAS_CHECK_IF_VALID(pThread);

		for(IAS_DFT_FACTORY<BackgroundJobEntry>::PtrHoldersCollection::iterator it=phcJobEntries.begin();
				it != phcJobEntries.end(); it++){

			BackgroundJobEntry *pEntry = *it;

			if(pEntry->getState() ==  BackgroundJobEntry::JS_Waiting){
				pResult=pEntry;
				break;
			}

		}

		if(bClosed)
			IAS_THROW(IAS::ItemNotFoundException());

		if(pResult == NULL){
			theLock.wait(theConditionEmpty);
		}

	}while(pResult == NULL);

	pResult->assignOwner(pThread);

	if(LogLevel::INSTANCE.isSystem()){
		String strId;
		pResult->getId(strId);
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "assigned:"<<strId);
	}

	return pResult;
}

/*************************************************************************/
void BackgroundJobsQueue::releaseEntry(BackgroundJobEntry *pEntry){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);

	if(LogLevel::INSTANCE.isSystem()){
		String strId;
		pEntry->getId(strId);
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "releasing:"<<strId);
	}

	pEntry->releaseOwner();
	theConditionEmpty.signal();
}
/*************************************************************************/
void BackgroundJobsQueue::removeEntry(BackgroundJobEntry *pEntry){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "???1:");

	Mutex::Locker aLocker(theLock);
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "???2:");
	phcJobEntries.delPointer(pEntry);
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "???4:");
	iNumEntries--;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "iNumEntries="<<iNumEntries);
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "???3:");
}
/*************************************************************************/
void BackgroundJobsQueue::close(){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);
	bClosed=true;
	theConditionEmpty.broadcast();
}
/*************************************************************************/
}
