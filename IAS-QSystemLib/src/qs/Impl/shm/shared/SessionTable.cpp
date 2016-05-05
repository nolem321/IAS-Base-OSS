/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/SessionTable.cpp
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
#include "SessionTable.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
/*************************************************************************/
SessionTable::SessionTable(size_t iSize):
	iSize(iSize),
	tabSessions(0),
	iMaxObjects(10),
	iRollbackSegment(10),
	mutex(true){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Created at: "<<((void*)this)<<", size="<<iSize);

	QS::SHM::SystemAllocator<Session> allocator;

	tabSessions = new(allocator.allocate(iSize))Session[iSize];
}
/*************************************************************************/
SessionTable::~SessionTable(){
	IAS_TRACER;
	IAS_THROW(InternalException("SessionTable destroyed."))
}
/*************************************************************************/
Session* SessionTable::createTransacted(){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	Session* pSession=findFreeSlotNoLock();
	pSession->setupTransacted();

	return pSession;
}
/*************************************************************************/
Session* SessionTable::createAutoCommit(){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	Session* pSession=findFreeSlotNoLock();
	pSession->setupAutoCommit();

	return pSession;
}
/*************************************************************************/
Session* SessionTable::findFreeSlotNoLock(){

	IAS_TRACER;

	int iIdx=0;

	while(iIdx<iSize && !tabSessions[iIdx].isFree())
		iIdx++;

	if(iIdx == iSize)
			IAS_THROW(InternalException("Out of resources, no sessions slots."));

	return tabSessions+iIdx;
}
/*************************************************************************/
void SessionTable::setMaxObjects(unsigned short iMaxObjects){
	IAS_TRACER;
	this->iMaxObjects=iMaxObjects;
}
/*************************************************************************/
void SessionTable::setRollbackSegment(unsigned short iRollbackSegment){
	IAS_TRACER;
	this->iRollbackSegment=iRollbackSegment;
}
/*************************************************************************/
short int SessionTable::getNumActiveSessions(){
	IAS_TRACER;

	Mutex::Locker  locker(mutex);

	//There is no session closing control on this level, so just count
	//Use for statistics only.

	short int iResult=0;
	for(int iIdx=0; iIdx<iSize;iIdx++)
		if(!tabSessions[iIdx].isFree())
			iResult++;

	return iResult;
}
/*************************************************************************/
}
}
}
}
