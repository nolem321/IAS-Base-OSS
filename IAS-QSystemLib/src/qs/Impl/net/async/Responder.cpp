/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Responder.cpp
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

#include <commonlib/commonlib.h>

#include "../Message.h"
#include "Session.h"
#include "Connection.h"
#include "Conversation.h"
#include "Engine.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async{

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

	Conversation::Key key = TypeTools::StringToInt(refDestination.getName().substr(21));

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "RKEY: "<<key);

	Engine::AutoResume ptrConversation(getSession()->getEngine()->getAvailableForWriting(key));

	//TODO (M) typeid check and static ?
	Message* pNetMessage=dynamic_cast<Message*>(pMessage);

	ptrConversation->putMessage(pNetMessage);

	return true;
}
/*************************************************************************/
}
}
}
}
