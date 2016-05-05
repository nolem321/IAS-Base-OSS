/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Sender.cpp
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
#include "Sender.h"
#include<qs/log/LogLevel.h>

#include "Session.h"
#include "Connection.h"
#include "../Message.h"
#include "Conversation.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Async{

/*************************************************************************/
Sender::Sender(Session* pSession, const API::Destination& refDestination):
	Manageable(pSession),
	myDestination(refDestination){

	IAS_TRACER;

}
/*************************************************************************/
Sender::~Sender() throw(){
	IAS_TRACER;

}
/*************************************************************************/
bool Sender::send(API::Message* pMessage){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pMessage);

	IAS_THROW(BadUsageException("Sending in asynchronous mode ? To whom ?"));

	return true;
}
/*************************************************************************/

}
}
}
}
