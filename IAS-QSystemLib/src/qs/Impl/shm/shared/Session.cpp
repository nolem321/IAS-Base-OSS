/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/Session.cpp
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
#include "Session.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "MsgEntry.h"
#include "../System.h"

#include "Subscription.h"
#include <algorithm>

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
/*************************************************************************/
Session::Session():
	iMode(SM_NotAllocated),
	mutex(true),
	mutexAlive(true,true){

	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"Created at: "<<((void*)this));
}
/*************************************************************************/
Session::~Session(){
	IAS_TRACER;
	//IAS_THROW(InternalException("Session destroyed."))
}
/*************************************************************************/
void Session::setupTransacted(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	setupNoLock(SM_Transacted);
}
/*************************************************************************/
void Session::setupAutoCommit(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	setupNoLock(SM_AutoCommit);
}
/*************************************************************************/
void Session::setupNoLock(Mode iMode){
	IAS_TRACER;

	if(isAllocatedNoLock())
		IAS_THROW(InternalException("Already allocated !!!"));

	this->iMode=iMode;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Allocated:"<<iMode<<", a="<<(void*)this);

	ptrSessionData=QS::SHM::QueueAllocator<SessionData>::Create(10,10);

	mutexAlive.lock();

}
/*************************************************************************/
void Session::commit(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
}
/*************************************************************************/
void Session::rollback(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	rollbackNoLock();
}
/*************************************************************************/
void Session::close(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	closeNoLock();

	mutexAlive.unlock();
}
/*************************************************************************/
void Session::tryToClean(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(iMode == SM_NotAllocated)
		return;

	if(!mutexAlive.trylock()){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," == Skipped");
		return;
	}

	closeNoLock();

	mutexAlive.unlock();
}
/*************************************************************************/
void Session::closeNoLock(){
	IAS_TRACER;

	rollbackNoLock();
	iMode = SM_NotAllocated;
	ptrSessionData=0;

}
/*************************************************************************/
void Session::rollbackNoLock(){
	IAS_TRACER;
}
/*************************************************************************/
JournalObjectEntry* Session::allocateJOE(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);
		return ptrSessionData->allocateJOE();
}
/*************************************************************************/
}
}
}
}
