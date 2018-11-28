/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Requester.cpp
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
#include "Requester.h"
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
Requester::Requester(Session* pSession,
					const API::Destination& outDestination,
					const API::Destination& inDestination):
	SHM::Receiver(pSession),
	outDestination(outDestination),
	joeOutputQueue(pSession->getSHMSession()->allocateJOE()){

	IAS_TRACER;

	QS::SHM::Shared::QueueTable* pQueueTable=pSession->getConnection()->getAttachment()->getQueueTable();

  const String& strName(inDestination.getName());


	if(strName.length() && strName[strName.length() - 1] == '*'){
		joeQueue.assignQueue(pQueueTable->createTemporary(strName.substr(0, strName.length() - 1))->open(), true);

	}else{
		openInputQueue(inDestination);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),joeQueue->getName()<<"="<<joeQueue->getQueueDataId());

	joeOutputQueue.assignQueue(pQueueTable->open(outDestination.getName()),false);
}
/*************************************************************************/
Requester::~Requester() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Requester::request(API::Message* pMessage){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pMessage);
	//TODO typeid check and static ?
	Message* pSystemMessage=dynamic_cast<Message*>(pMessage);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"ID: jakies id by sie przydalo.");
	pSystemMessage->getAttributes()->setReplyTo(joeQueue->getName());
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),joeQueue->getName()<<"="<<joeQueue->getQueueDataId());

	return joeOutputQueue->put(pSystemMessage->getEntry());
}
/*************************************************************************/

}
}
}
