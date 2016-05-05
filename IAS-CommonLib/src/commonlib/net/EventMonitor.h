/*
 * File: IAS-CommonLib/src/commonlib/net/EventMonitor.h
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
#ifndef _IAS_Net_EventMonitor_H_
#define _IAS_Net_EventMonitor_H_

#include <commonlib/logger/logger.h>
#include <commonlib/memory/memory.h>
#include <commonlib/threads/Thread.h>
#include <commonlib/threads/Runnable.h>
#include <commonlib/threads/Mutex.h>
#include <commonlib/threads/Condition.h>

#include "EventHandler.h"

namespace IAS {
namespace Net {


/*************************************************************************/
/** The EventMonitor class.
 *
 */
class EventMonitor {
public:

	virtual ~EventMonitor() throw(){};

	void addHandler(EventHandler* pEventHandler);
	void removeHandler(EventHandler* pEventHandler);

	void getReady(EventHandler* &refPtrHander, EventHandler::EventType& iEvent);
	void afterService(EventHandler* pEventHandler);

	typedef IAS_DFT_FACTORY<EventMonitor>::PtrHolder PtrHolder;
	static EventMonitor* Create();

	class ServiceTask{
		public:

			ServiceTask(EventMonitor* pEventMonitor):
				pEventMonitor(pEventMonitor),
				pHandler(0),
				iEvent(EventHandler::ET_None){
				pEventMonitor->getReady(pHandler,iEvent);
			}

			void work(){
				//IAS_LOG(true,"Service: "<<(void*)pHandler);
				pHandler->handle(iEvent);
			}

			~ServiceTask(){
				pEventMonitor->afterService(pHandler);
			}

	protected:
		EventMonitor* pEventMonitor;
		EventHandler* pHandler;
		EventHandler::EventType iEvent;
	};

	/*************************************************************************/
	class Worker{
		public:
			Worker(Net::EventMonitor*  pEventMonitor);
			virtual void work();

		protected:
			Net::EventMonitor*  pEventMonitor;

	};

	/*************************************************************************/

	class ThreadedWorker : public Worker, public Thread, public Runnable{
		public:
		ThreadedWorker(Net::EventMonitor*  pEventMonitor);
		virtual void run();
	};

	/*************************************************************************/

protected:

	virtual void addHandlerImpl(EventHandler* pEventHandler)=0;
	virtual void removeHandlerImpl(EventHandler* pEventHandler)=0;
	virtual void getReadyImpl(EventHandler* &refPtrHander, EventHandler::EventType& iEvent)=0;
	virtual void afterServiceImpl(EventHandler* pEventHandler)=0;

	IAS_DFT_FACTORY<EventHandler>::PtrHoldersCollection phcHandlers;

private:

	Mutex mutexHandlerList;

};
/*************************************************************************/
}
}

#endif /* _IAS_Net_EventMonitor_H_ */
