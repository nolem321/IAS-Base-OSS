/*
 * File: WaitingRoom.cpp
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

#include "WaitingRoom.h"

#include "WaitingRoomQueue.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task {

/*************************************************************************/
WaitingRoom::WaitingRoom(GlobalContext* pGlobalContext):
	pGlobalContext(pGlobalContext){
	IAS_TRACER;
}

/*************************************************************************/
WaitingRoom::~WaitingRoom() throw(){
	IAS_TRACER;
}
/*************************************************************************/
WaitingRoomQueue *WaitingRoom::createQueue(const String& strQueueName){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmWaitingRoomQueues.count(strQueueName) > 0)
		return hmWaitingRoomQueues[strQueueName];

	return hmWaitingRoomQueues[strQueueName] = IAS_DFT_FACTORY<WaitingRoomQueue>::Create(this);
}
/*************************************************************************/
WaitingRoomQueue *WaitingRoom::getQueue(const String& strQueueName)const{

	IAS_TRACER;

	Mutex::Locker locker(const_cast<WaitingRoom*>(this)->mutex);

	if(hmWaitingRoomQueues.count(strQueueName) == 0)
		IAS_THROW(ItemNotFoundException("Task queue not defined: " + strQueueName));

	return const_cast<WaitingRoomQueue *>(hmWaitingRoomQueues.at(strQueueName));
}
/*************************************************************************/
}
}
}
}
}
