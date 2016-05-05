/*
 * File: IAS-CommonLib/src/commonlib/net/EventHandler.cpp
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
#include "EventHandler.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace Net {

/*************************************************************************/
EventHandler::EventHandler(FileHandle* pFileHandle):
		pFileHandle(pFileHandle),
	bDeletePending(false),
	iUsageCount(0),
	iSubscription(ET_Error),
	iActiveEventsMask(ET_None){
	IAS_TRACER;
	pFileHandle->setNonBlocking();
}
/*************************************************************************/
EventHandler::~EventHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void EventHandler::handle(EventType iEvent){
	IAS_TRACER;

	switch(iEvent){

		case ET_InputReady:
			IAS_LOG(LogLevel::INSTANCE.isInfo(), "Input ready event: "<<pFileHandle->getFD());
			onInputReady();
			break;

		case ET_OutputReady:
			IAS_LOG(LogLevel::INSTANCE.isInfo(), "Output ready event: "<<pFileHandle->getFD());
			onOutputReady();
			break;

		case ET_Timeout:
			IAS_LOG(LogLevel::INSTANCE.isInfo(), "Timeout event: "<<pFileHandle->getFD());
			onTimeout();
			break;

		case ET_Error:
			IAS_LOG(LogLevel::INSTANCE.isInfo(), "Error event: "<<pFileHandle->getFD());
			onError();
			break;

		default:
			IAS_THROW(InternalException(String("Unknown event type:")+TypeTools::IntToString(iEvent)));
	}

}
/*************************************************************************/
bool EventHandler::isSubscribed(EventType iEventType)const{
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "subscription="<<iSubscription<<", check="<<iEventType<<", res="<<(iEventType & iSubscription));

	return iEventType & iSubscription;
}
/*************************************************************************/
void EventHandler::subscribe(EventType iEventType){
	IAS_TRACER;
	iSubscription = static_cast<EventType>(iSubscription |iEventType);
}
/*************************************************************************/
void EventHandler::unsubscribe(EventType iEventType){
	IAS_TRACER;
	iSubscription = static_cast<EventType>(iSubscription & ~iEventType);
}
/*************************************************************************/
void EventHandler::addUsage(){
	IAS_TRACER;
	Mutex::Locker locker(mutexUsage);
	iUsageCount++;
}
/*************************************************************************/
bool EventHandler::removeUsage(){
	IAS_TRACER;

	Mutex::Locker locker(mutexUsage);

	if(iUsageCount==0)
		IAS_THROW(InternalException("iUsageCount==0 in the event handler."));

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Usage count: "<<iUsageCount);


	return --iUsageCount == 0;
}
/*************************************************************************/
bool EventHandler::isDeletePending(){
	IAS_TRACER;
	Mutex::Locker locker(mutexUsage);
	return bDeletePending && iUsageCount == 0;
}
/*************************************************************************/
void EventHandler::setDeletePending(){
	IAS_TRACER;
	Mutex::Locker locker(mutexUsage);
	bDeletePending=true;
}
/*************************************************************************/
void EventHandler::onInputReady(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Input ready event: - default."<<pFileHandle->getFD());
}
/*************************************************************************/
void EventHandler::onOutputReady(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Output ready event: - default."<<pFileHandle->getFD());
}

/*************************************************************************/
void EventHandler::onTimeout(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Timeout event: "<<pFileHandle->getFD());
}
/*************************************************************************/
void EventHandler::onError(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isError(), "Error event: "<<pFileHandle->getFD());
	IAS_THROW(InternalException("Unimplemented error event handler."));
}
/*************************************************************************/
}
}
