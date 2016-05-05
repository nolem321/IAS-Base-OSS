/*
 * File: IAS-CommonLib/src/commonlib/net/EventMonitor.cpp
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
#include "EventMonitor.h"

#include <commonlib/commonlib.h>


#include "epoll/EventMonitor.h"
#include "pollset/EventMonitor.h"

namespace IAS {
namespace Net {

/*************************************************************************/
EventMonitor* EventMonitor::Create(){
	IAS_TRACER;
#ifdef __linux
	return IAS_DFT_FACTORY<EPoll::EventMonitor>::Create();
#else
	return IAS_DFT_FACTORY<PollSet::EventMonitor>::Create();
#endif

}
/*************************************************************************/
void EventMonitor::addHandler(EventHandler* pEventHandler){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pEventHandler);

	Mutex::Locker locker(mutexHandlerList);
	addHandlerImpl(pEventHandler);
	phcHandlers.addPointer(pEventHandler);
}
/*************************************************************************/
void EventMonitor::removeHandler(EventHandler* pEventHandler){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pEventHandler);

	Mutex::Locker locker(mutexHandlerList);

	if(pEventHandler->removeUsage()){
		removeHandlerImpl(pEventHandler);
		phcHandlers.delPointer(pEventHandler);
	}

}
/*************************************************************************/
void EventMonitor::getReady(EventHandler* &refPtrHander, EventHandler::EventType& iEvent){
	IAS_TRACER;
	refPtrHander=NULL;
	getReadyImpl(refPtrHander,iEvent);

	if(refPtrHander)
		refPtrHander->addUsage();
}
/*************************************************************************/
void EventMonitor::afterService(EventHandler* pEventHandler){
	IAS_TRACER;

	Mutex::Locker locker(mutexHandlerList);
	pEventHandler->removeUsage();

	if(pEventHandler->isDeletePending()){
		removeHandlerImpl(pEventHandler);
		phcHandlers.delPointer(pEventHandler);
	}else{
		afterServiceImpl(pEventHandler);
	}

}
/*************************************************************************/
EventMonitor::Worker::Worker(Net::EventMonitor* pEventMonitor):
		pEventMonitor(pEventMonitor){}
/*************************************************************************/
void EventMonitor::Worker::work(){
	IAS_TRACER;

	Net::EventMonitor::ServiceTask service(pEventMonitor);
	service.work();
}
/*************************************************************************/
EventMonitor::ThreadedWorker::ThreadedWorker(Net::EventMonitor* pEventMonitor):
		Worker(pEventMonitor),
		Thread(this){}
/*************************************************************************/
void EventMonitor::ThreadedWorker::run(){
	IAS_TRACER;

	//TODO (L) check stream cancellation.
	Thread::Cancellation ca(false);
	//This is mandatory ! otherwise stop() will can cancel while in destructor.

	while(true){

		Thread::Cancellation::Test();
		work();
	}

}
/*************************************************************************/
}
}
