/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Responder.cpp
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
#include "Responder.h"
#include<qs/log/LogLevel.h>

#include "Session.h"
#include "Connection.h"
#include "Message.h"
#include <commonlib/commonlib.h>
#include <qs/Impl/shm/Attachment.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>

#include <qs/Impl/shm/shared/JournalObjectEntry.h>


namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Responder::Responder(Session* pSession):
	Manageable(pSession){

	IAS_TRACER;

}
/*************************************************************************/
Responder::~Responder() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Responder::respond(API::Message* pMessage, const API::Destination& refDestination){
	IAS_TRACER;

	//TODO (L) send without open ?
	//TODO (L) czy nie zamknie sie kolejka przed commit/rollback ?

	Shared::QueueTable* pQueueTable=getSession()->getConnection()->getAttachment()->getQueueTable();
	QS::SHM::Shared::JournalObjectEntry::Holder joeQueue(getSession()->getSHMSession()->allocateJOE());
	joeQueue.assignQueue(pQueueTable->open(refDestination.getName()),false);


	IAS_CHECK_IF_NULL(pMessage);
	//TODO typeid check and static ?
	Message* pSystemMessage=dynamic_cast<Message*>(pMessage);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"ID: jakies id by sie przydalo.");

	return joeQueue->put(pSystemMessage->getEntry());
}
/*************************************************************************/

}
}
}
