/*
 * File: IAS-CommonLib/src/commonlib/net/PollSet/EventMonitor.cpp
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

#ifdef _AIX
#include "EventMonitor.h"
#include "../EventHandler.h"

#include <sys/poll.h>
#include <sys/pollset.h>

#include <unistd.h>

namespace IAS {
namespace Net {
namespace PollSet {

/*************************************************************************/
EventMonitor::EventMonitor(){
	IAS_TRACER;
	iPollSetDescriptor = pollset_create(10240);

	 if(iPollSetDescriptor == -1)
	    IAS_THROW(SystemException("pollset_create:"));

}
/*************************************************************************/
EventMonitor::~EventMonitor() throw(){
	IAS_TRACER;

	pollset_destroy(iPollSetDescriptor);
}
/*************************************************************************/
void EventMonitor::addHandlerImpl(EventHandler* pEventHandler){
	IAS_TRACER;
	modifyPollSet(pEventHandler,PS_ADD);
}
/*************************************************************************/
void EventMonitor::afterServiceImpl(EventHandler* pEventHandler){
	IAS_TRACER;

	modifyPollSet(pEventHandler,PS_MOD);
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"after event for:"<<pEventHandler->getFileHandle());

}
/*************************************************************************/
void EventMonitor::removeHandlerImpl(EventHandler* pEventHandler){
	IAS_TRACER;
	modifyPollSet(pEventHandler, PS_DELETE);
}
/*************************************************************************/
void EventMonitor::modifyPollSet(EventHandler* pEventHandler,  int iAction){
	IAS_TRACER;

	struct poll_ctl ctl;

	ctl.cmd=iAction;
	ctl.events = 0;
	ctl.fd = pEventHandler->getFileHandle()->getFD();

	if(iAction == PS_DELETE)
		hmFileToEventMonitor.erase(ctl.fd);
	else
		hmFileToEventMonitor[ctl.fd]=pEventHandler;


	if(pEventHandler->isSubscribed(EventHandler::ET_InputReady))
		ctl.events |= POLLIN;

	if(pEventHandler->isSubscribed(EventHandler::ET_OutputReady))
		ctl.events |= POLLOUT;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"fd="<<pEventHandler->getFileHandle()<<", action="<<iAction<<", events="<<ctl.events);

	if( pollset_ctl(iPollSetDescriptor, &ctl, 1)){
	    IAS_THROW(SystemException("pollset_ctl:"));
	}

}
/*************************************************************************/
void EventMonitor::getReadyImpl(EventHandler* &refPtrHander, EventHandler::EventType &iEvent){
	IAS_TRACER;

	//TODO (M) thread worker and consumers and event queue ?

	 struct pollfd event;
	 int iResult;

	 {
		 Thread::Cancellation ca(true);
		 iResult=pollset_poll(iPollSetDescriptor, &event, 1, -1);
	 }

	 switch(iResult){

		case 1:
			if(hmFileToEventMonitor.count(event.fd) == 0)
				IAS_THROW(InternalException("hmFileToEventMonitor.count(event.fd) == 0"));

			refPtrHander=hmFileToEventMonitor[event.fd];
			iEvent=getEventType(event.events);
			break;

		case 0:
			IAS_THROW(EndOfDataException());
			break;

		case -1:
			if(errno == EINTR)
				IAS_THROW(EndOfDataException());

			IAS_THROW(SystemException());
			break;

		default:
			IAS_THROW(InternalException("Unknown result in EventMonitor::getReady()"));
	}

}
/*************************************************************************/
EventHandler::EventType EventMonitor::getEventType(int iPollSetType)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"event="<<iPollSetType);

	if((iPollSetType & POLLPRI) ||
	   (iPollSetType & POLLPRI))
			return EventHandler::ET_Error;

	if(iPollSetType & POLLIN)
		return EventHandler::ET_InputReady;

	if(iPollSetType & POLLOUT)
		return EventHandler::ET_OutputReady;

	IAS_THROW(InternalException(String("Unknow PollSet event:")+TypeTools::IntToString(iPollSetType)))
}
/*************************************************************************/
}
}
}
#endif
