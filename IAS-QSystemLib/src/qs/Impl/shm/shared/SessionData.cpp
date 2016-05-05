/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/SessionData.cpp
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
#include "SessionData.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include "MsgEntry.h"
#include "../Attachment.h"
#include "Queue.h"
#include "JournalObjectEntry.h"

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
SessionData::SessionData(SessionDataSize iObjectEntires, SessionDataSize iDataEntires):
	iObjectEntires(iObjectEntires),
	iDataEntires(iDataEntires),
	tabObjectJournal(0){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Created at: "<<((void*)this));

	//TODO ptrHolders
	//TODO more efficient implementation
	QS::SHM::QueueAllocator<JournalObjectEntry> allocator;
	tabObjectJournal = new(allocator.allocate(iObjectEntires))JournalObjectEntry[iObjectEntires];

}
/*************************************************************************/
SessionData::~SessionData(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Destroyed at: "<<((void*)this));

	if(tabObjectJournal){

		for(int iIdx=0; iIdx <  iObjectEntires; iIdx++)
			if(!tabObjectJournal[iIdx].free())
				tabObjectJournal[iIdx].rollback();

		QS::SHM::QueueAllocator<JournalObjectEntry> allocator;
		allocator.deallocate(tabObjectJournal,this->iObjectEntires);
		tabObjectJournal=0;
	}
}
/*************************************************************************/
JournalObjectEntry* SessionData::allocateJOE(){
	IAS_TRACER;

	int iIdx=0;

	while(iIdx < iObjectEntires && !tabObjectJournal[iIdx].free())
		iIdx++;

	if(iIdx >=  iObjectEntires)
		IAS_THROW(ConfigException("Out of object entries in a rollback segment."));

	tabObjectJournal[iIdx].allocate();
	return tabObjectJournal+iIdx;
}
/*************************************************************************/
void SessionData::rollback(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionData::commit(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
