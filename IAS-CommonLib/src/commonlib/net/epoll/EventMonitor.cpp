/*
 * File: IAS-CommonLib/src/commonlib/net/epoll/EventMonitor.cpp
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
#ifdef __linux
#include "EventMonitor.h"
#include "../EventHandler.h"

#include <sys/epoll.h>
#include <unistd.h>

namespace IAS {
namespace Net {
namespace EPoll {

/*************************************************************************/
EventMonitor::EventMonitor():
	bEageTriggering(false){
	IAS_TRACER;
	iEPollDescriptor = epoll_create1(0);

	 if(iEPollDescriptor == -1)
	    IAS_THROW(SystemException("epoll_create1:"));

}
/*************************************************************************/
EventMonitor::~EventMonitor() throw(){
	IAS_TRACER;

	close(iEPollDescriptor);
}
/*************************************************************************/
void EventMonitor::addHandlerImpl(EventHandler* pEventHandler){
	IAS_TRACER;
	modifyEPoll(pEventHandler,EPOLL_CTL_ADD);
}
/*************************************************************************/
void EventMonitor::afterServiceImpl(EventHandler* pEventHandler){
	IAS_TRACER;

	modifyEPoll(pEventHandler,EPOLL_CTL_MOD);
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"after event for:"<<pEventHandler->getFileHandle());

}
/*************************************************************************/
void EventMonitor::removeHandlerImpl(EventHandler* pEventHandler){
	IAS_TRACER;
	modifyEPoll(pEventHandler,EPOLL_CTL_DEL);
}
/*************************************************************************/
void EventMonitor::modifyEPoll(EventHandler* pEventHandler,  int iAction){
	IAS_TRACER;

	struct epoll_event event;

	event.data.ptr = pEventHandler;
	event.events =  (bEageTriggering ? EPOLLET : 0 )| EPOLLONESHOT; //TODO (M) types

	if(pEventHandler->isSubscribed(EventHandler::ET_InputReady))
		event.events |= EPOLLIN;

	if(pEventHandler->isSubscribed(EventHandler::ET_OutputReady))
		event.events |= EPOLLOUT;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"fd="<<pEventHandler->getFileHandle()<<", action="<<iAction<<", events="<<event.events);

	if( epoll_ctl(iEPollDescriptor, iAction, pEventHandler->getFileHandle()->getFD(), &event)){
	    IAS_THROW(SystemException("epoll_ctl:"));
	}

}
/*************************************************************************/
void EventMonitor::getReadyImpl(EventHandler* &refPtrHander, EventHandler::EventType &iEvent){
	IAS_TRACER;

	//TODO (M) thread worker and consumers and event queue ?

	 struct epoll_event event;
	 int iResult;

	 {
		 Thread::Cancellation ca(true);
		 iResult=epoll_wait(iEPollDescriptor, &event, 1, -1);
	 }

	 switch(iResult){

		case 1:
			refPtrHander=static_cast<EventHandler*>(event.data.ptr);
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
EventHandler::EventType EventMonitor::getEventType(int iEPollType)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"event="<<iEPollType);

	if((iEPollType & EPOLLERR) ||
	   (iEPollType & EPOLLHUP))
			return EventHandler::ET_Error;

	if(iEPollType & EPOLLIN)
		return EventHandler::ET_InputReady;

	if(iEPollType & EPOLLOUT)
		return EventHandler::ET_OutputReady;

	IAS_THROW(InternalException(String("Unknow epoll event:")+TypeTools::IntToString(iEPollType)))
}
/*************************************************************************/
}
}
}
#endif
