/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobThread.cpp
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
#include "BackgroundJobThread.h"

#include "BackgroundJob.h"
#include "BackgroundJobEntry.h"
#include "BackgroundJobsQueue.h"
#include "../exception/ItemNotFoundException.h"

#include "../time/Timestamp.h"

namespace IAS {
/*************************************************************************/
BackgroundJobThread::BackgroundJobThread(BackgroundJobsQueue* pQueue):Thread(this),pQueue(pQueue),bEndOfWork(false){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pQueue);
}

/*************************************************************************/
BackgroundJobThread::~BackgroundJobThread() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void BackgroundJobThread::setEndOfWorkState(){
	Mutex::Locker aLocker(theLock);
	bEndOfWork=true;
}
/*************************************************************************/
bool BackgroundJobThread::getEndOfWorkState(){
	Mutex::Locker aLocker(theLock);
	return bEndOfWork;
}
/*************************************************************************/
void BackgroundJobThread::run(){
	IAS_TRACER;

	while(!getEndOfWorkState()){

		IAS_CHECK_IF_VALID(pQueue);

		//TODO (L) auto relaease

		try{

			BackgroundJobEntry *pEntry = pQueue->assignEntry(this);

			IAS_LOG(LogLevel::INSTANCE.isSystem(), "Has entry:"<<(void*)this);

			IAS_CHECK_IF_VALID(pEntry);

			if(pEntry->decrementAndGetRetryCount() + 1 < 0){
				cancelJob(pEntry);
			}else{
				startJob(pEntry);
			}

		}catch(ItemNotFoundException& e){
			IAS_LOG(LogLevel::INSTANCE.isSystem(), "Exception:"<<(void*)this);
			IAS_LOG(IAS::LogLevel::INSTANCE.bIsDetailedInfo, "ItemNotFoundException:"<<(void*)this);
		}

	}/* main loop */

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Finish:"<<(void*)this);
}
/*************************************************************************/
void BackgroundJobThread::startJob(BackgroundJobEntry* pEntry){
	IAS_TRACER;

	bool bSucces = true;

	BackgroundJob* pJob=pEntry->getBackgroundJob();

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "START:"<<(void*)this);

	try{
		pJob->onStart();
	}catch(IAS::Exception& e){
		bSucces=false;
		pJob->onError(e);
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "STOP1:"<<(void*)this);

	if(bSucces){
		removeJob(pEntry);
	}else{
		pQueue->releaseEntry(pEntry);
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "STOP2:"<<(void*)this);
}
/*************************************************************************/
void BackgroundJobThread::cancelJob(BackgroundJobEntry* pEntry){
	IAS_TRACER;

	BackgroundJob* pJob=pEntry->getBackgroundJob();

	try{
		pJob->onCancel();
	}catch(...){
		IAS_LOG(IAS::LogLevel::INSTANCE.bIsError, "an exception on job cancel !");
	}

	removeJob(pEntry);
}
/*************************************************************************/
void BackgroundJobThread::removeJob(BackgroundJobEntry* pEntry){
	IAS_TRACER;
	pQueue->removeEntry(pEntry);
}
/*************************************************************************/
}
