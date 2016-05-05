/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Controller.cpp
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
#include "Controller.h"
#include<qs/log/LogLevel.h>

#include "Session.h"
#include "Connection.h"
#include "Message.h"
#include <commonlib/commonlib.h>
#include <qs/Impl/shm/Attachment.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Controller::Controller(Session* pSession, const API::Destination& refDestination):
	Manageable(pSession),
	joeQueue(pSession->getSHMSession()->allocateJOE()),
	myDestination(refDestination){

	IAS_TRACER;

	Shared::QueueTable* pQueueTable=getSession()->getConnection()->getAttachment()->getQueueTable();

	joeQueue.assignQueue(pQueueTable->open(myDestination.getName()),false);
}
/*************************************************************************/
Controller::~Controller() throw(){
	IAS_TRACER;

}
/*************************************************************************/
unsigned int Controller::getNumMessages(){
	IAS_TRACER;

	return joeQueue->getNumMsgs();
}
/*************************************************************************/

}
}
}
