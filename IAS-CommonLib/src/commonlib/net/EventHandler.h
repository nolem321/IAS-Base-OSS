/*
 * File: IAS-CommonLib/src/commonlib/net/EventHandler.h
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
#ifndef _IAS_Net_EventHandler_H_
#define _IAS_Net_EventHandler_H_

#include <commonlib/memory/memory.h>
#include <commonlib/threads/Mutex.h>
#include <commonlib/threads/Condition.h>

#include "FileHandle.h"

namespace IAS {
namespace Net {

/*************************************************************************/
/** The EventHandler class.
 *
 */
class EventHandler {
public:

	enum EventType{
		ET_None         = 0x00,
		ET_InputReady   = 0x01,
		ET_OutputReady  = 0x02,
		ET_Timeout      = 0x04,
		ET_Error        = 0x10

	};

	virtual ~EventHandler() throw();

	virtual void handle(EventType iEvent);

	inline FileHandle* getFileHandle()const {return pFileHandle;};

	bool isSubscribed(EventType iEventType)const;

protected:

	EventHandler(FileHandle* pFileHandle);

	virtual void onInputReady();
	virtual void onOutputReady();

	virtual void onTimeout();
	virtual void onError();

	FileHandle*   pFileHandle;

	void setupAvailablity();
	void setupTimeout(int iTimeoutMS);
	void setupError();

	EventType iActiveEventsMask;

	friend class Factory<EventHandler>;

	Mutex mutexUsage;
	Mutex mutexService;

	void addUsage();
	bool removeUsage();

	bool isDeletePending();
	void setDeletePending();

	void subscribe(EventType iEventType);
	void unsubscribe(EventType iEventType);

private:
	unsigned short iUsageCount;

	bool           bDeletePending;
	EventType      iSubscription;

	friend class   EventMonitor;
};

/*************************************************************************/
}
}

#endif /* _IAS_Net_EventHandler_H_ */
