/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Receiver.cpp
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
#include "Receiver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../Message.h"

#include "Session.h"
#include "Connection.h"
#include "System.h"
#include <set>
#include <commonlib/commonlib.h>

#include <qs/Impl/net/pump/MsgPumpFactory.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{
/*************************************************************************/
Receiver::Receiver(Session* pSession):
	Manageable(pSession),
	iCounter(0),
	myDestination("__FAKE__"){
	IAS_TRACER;
}

/*************************************************************************/
Receiver::~Receiver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receiver::open(const API::Destination& refDestination){
	IAS_TRACER;
}
/*************************************************************************/
API::Message* Receiver::receive(int iTimeWait, API::Attributes* pSelector){
	IAS_TRACER;

	IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage(IAS_DFT_FACTORY<Message>::Create());

	Session *pSession = getSession();

	pSession->setTimeout(iTimeWait);

	Pump::MsgPumpFactory::DataPumpPtr ptrPump(pMsgPumpFactory->createInputPump(pSession->getBlockIO(),ptrMessage));

	while(ptrPump->pump() != IAS::Net::IBlockIO::RC_OK)
		/* repeat */;

	pSession->updateAttributes(ptrMessage->getAttributes());

	return ptrMessage.pass();
}

/*************************************************************************/

}
}
}
}
