/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Browser.cpp
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
#include "Browser.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Message.h"
#include "Session.h"
#include "Connection.h"

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/System.h>
#include <qs/Impl/shm/shared/Queue.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <qs/Impl/shm/shared/QueueTable.h>


namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Browser::Browser(Session* pSession, const API::Destination& refDestination):
	Receiver(pSession),
	iLocator(Shared::Queue::C_StartLocation){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Browser: "<<refDestination.getName());

	openInputQueue(refDestination);
}
/*************************************************************************/
Browser::~Browser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int Browser::skip(unsigned int iOffset){
	IAS_TRACER;

	if(!joeQueue)
		IAS_THROW(InternalException("Better exception - not opened."));

	QS::SHM::Shared::MsgEntry entry;

	unsigned int iResult = 0;

	while(iOffset-- && joeQueue->browse(entry,iLocator,0))
		iResult++;

	return iResult;
}
/*************************************************************************/
API::Message* Browser::receive(int iTimeWait, API::Attributes* pSelector){

	IAS_TRACER;

	if(!joeQueue)
		IAS_THROW(InternalException("Better exception - not opened."));

	QS::SHM::Shared::MsgEntry entry;
	if(!joeQueue->browse(entry,iLocator,iTimeWait))
		IAS_THROW(EndOfDataException(joeQueue->getName()+"No more messages."));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;
	ptrNewMessage = IAS_DFT_FACTORY<Message>::Create<const Shared::MsgEntry& >(entry);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"ID: no id for messages :))");

	return ptrNewMessage.pass();
}
/*************************************************************************/
}
}
}
