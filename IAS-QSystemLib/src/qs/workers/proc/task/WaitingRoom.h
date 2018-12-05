/*
 * File: WaitingRoom.h
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


#ifndef _IAS_QS_Workers_Proc_Task_WaitingRoom_H_
#define _IAS_QS_Workers_Proc_Task_WaitingRoom_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace Task {

class WaitingRoomQueue;
/*************************************************************************/
/** The WaitingRoom class.
 *
 */
class WaitingRoom {
public:

	virtual ~WaitingRoom() throw();

	WaitingRoomQueue *createQueue(const String& strQueueName);
	WaitingRoomQueue *getQueue(const String& strQueueName)const;

	inline GlobalContext* getGlobalContext()const{
		return pGlobalContext;
	}

protected:

	WaitingRoom(GlobalContext* pGlobalContext);

	Mutex mutex;

	typedef HashMapStringToPointer<WaitingRoomQueue> WaitingRoomQueueMap;

	WaitingRoomQueueMap hmWaitingRoomQueues;
	GlobalContext* pGlobalContext;

	friend class Factory<WaitingRoom>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Task_WaitingRoom_H_ */
