/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Requester.cpp
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
#include "Engine.h"

#include "../Message.h"
#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Async{

/*************************************************************************/
Requester::Requester(Session* pSession,
					const API::Destination& outDestination,
					const API::Destination& inDestination):
	aDestination(outDestination),
	Async::Receiver(pSession){

	IAS_TRACER;

}
/*************************************************************************/
Requester::~Requester() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Requester::request(API::Message* pMessage){
	IAS_TRACER;

	/*
	 * This is theoretically possible.
	 */

	Conversation::Key key = TypeTools::StringToInt(aDestination.getName());
	Engine::AutoResume ptrConversation(getSession()->getEngine()->getAvailableForWriting(key));

	//TODO (M) typeid check and static ?
	Message* pNetMessage=dynamic_cast<Message*>(pMessage);

	ptrConversation->putMessage(pNetMessage);

	StringStream ssValue;
	ssValue<<ptrConversation->getKey();
	pNetMessage->getAttributes()->setReplyTo(aDestination.getName());

	return true;
}
/*************************************************************************/

}
}
}
}
