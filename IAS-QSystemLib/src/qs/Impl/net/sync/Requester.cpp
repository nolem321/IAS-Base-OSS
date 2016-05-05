/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Requester.cpp
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
#include "../Message.h"
#include <commonlib/commonlib.h>

#include <qs/Impl/net/pump/MsgPumpFactory.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
Requester::Requester(Session* pSession,
					const API::Destination& outDestination,
					const API::Destination& inDestination):
	outDestination(outDestination),
	Sync::Receiver(pSession){

	IAS_TRACER;

}
/*************************************************************************/
Requester::~Requester() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Requester::request(API::Message* pMessage){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pMessage);
	//TODO (M) typeid check and static ?
	Message* pNetMessage=dynamic_cast<Message*>(pMessage);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"TODO ! generate ID ?.");
	pNetMessage->getAttributes()->setReplyTo("Net");

	Session *pSession = getSession();

	pSession->setTimeout();

	pNetMessage->setHost(pSession->getConnection()->getHost());
	pNetMessage->setResource(outDestination.getName());

	Pump::MsgPumpFactory::DataPumpPtr ptrPump(pMsgPumpFactory->createOutputPump(pSession->getBlockIO(),pNetMessage));

	while(ptrPump->pump() != IAS::Net::IBlockIO::RC_OK)
		/* repeat */;

	pSession->updateAttributes(pNetMessage->getAttributes());

	return true;
}
/*************************************************************************/

}
}
}
}
