/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobEntry.cpp
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
#include "BackgroundJobEntry.h"
#include "BackgroundJob.h"

#include "../time/Timestamp.h"

namespace IAS {

/*************************************************************************/
BackgroundJobEntry::BackgroundJobEntry(BackgroundJob* pBackgroundJob, int iRetryCount){
	IAS_TRACER;

	StringStream ssId;
	ssId<<"BJE_"<<(void*)this;
	strId=ssId.str();

	IAS_CHECK_IF_NULL(pBackgroundJob);
	ptrBackgroundJob=pBackgroundJob;

	this->iRetryCount=iRetryCount;
	this->pThread=NULL;
	this->iState=JS_Waiting;
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"New BJE: "<<strId);

}
/*************************************************************************/
BackgroundJobEntry::~BackgroundJobEntry() throw(){
	IAS_TRACER;
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Deleted BJE: "<<strId);
}
/*************************************************************************/
BackgroundJob* BackgroundJobEntry::getBackgroundJob(){
	IAS_TRACER;
	return ptrBackgroundJob;
}
/*************************************************************************/
int BackgroundJobEntry::getRetryCount(){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);
	return iRetryCount;
}
/*************************************************************************/
int BackgroundJobEntry::decrementAndGetRetryCount(){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);
	--iRetryCount;
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"RetryCount [ "<<strId<<"]:"<<iRetryCount);
	return iRetryCount;
}
/*************************************************************************/
void BackgroundJobEntry::getId(String& strId){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);
	strId = this->strId;
}
/*************************************************************************/
void BackgroundJobEntry::assignOwner(BackgroundJobThread* pThread){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);

	IAS_CHECK_IF_VALID(pThread);

	if(this->pThread != NULL)
		IAS_THROW(InternalException("BJE has an owner set !"));

	this->pThread=pThread;
	this->iState=JS_Running;
}
/*************************************************************************/
void BackgroundJobEntry::releaseOwner(){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);

	if(pThread==NULL)
		IAS_LOG(IAS::LogLevel::INSTANCE.isError(),"no owner but releaseOwner() called.")

	pThread=NULL;
	iState=JS_Waiting;
}
/*************************************************************************/
int BackgroundJobEntry::getState(){
	IAS_TRACER;
	Mutex::Locker aLocker(theLock);
	return iState;
}
/*************************************************************************/
}
