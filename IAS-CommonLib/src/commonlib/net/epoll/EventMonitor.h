/*
 * File: IAS-CommonLib/src/commonlib/net/epoll/EventMonitor.h
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
#ifndef _IAS_Net_EPoll_EventMonitor_H_
#define _IAS_Net_EPoll_EventMonitor_H_

#include <commonlib/commonlib.h>

#include "../EventMonitor.h"
namespace IAS {
namespace Net {
namespace EPoll {

/*************************************************************************/
/** The EventMonitor class.
 *
 */
class EventMonitor : public ::IAS::Net::EventMonitor{
public:

	virtual ~EventMonitor() throw();


protected:

	EventMonitor();

	virtual void addHandlerImpl(EventHandler* pEventHandler);
	virtual void removeHandlerImpl(EventHandler* pEventHandler);
	virtual void getReadyImpl(EventHandler* &refPtrHander, EventHandler::EventType &iEvent);
	virtual void afterServiceImpl(EventHandler* pEventHandler);

	int         iEPollDescriptor;

	bool        bEageTriggering;

	EventHandler::EventType getEventType(int iEpollType)const;

	void modifyEPoll(EventHandler* pEventHandler, int iAction);

	friend class Factory<EventMonitor>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_Net_EPoll_EventMonitor_H_ */
#endif
