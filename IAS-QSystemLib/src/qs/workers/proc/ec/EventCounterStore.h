/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/EventCounterStore.h
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
#ifndef _IAS_QS_Workers_Proc_EC_EventCounterStore_H_
#define _IAS_QS_Workers_Proc_EC_EventCounterStore_H_

#include <commonlib/commonlib.h>

#include "EventCounter.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {

/*************************************************************************/
/** The EventCounterStore class.
 *
 */
class EventCounterStore {
public:

	virtual ~EventCounterStore() throw();


	void addEventCounter(const String& strName, EventCounter* pEventCounter);
	EventCounter* lookup(const String& strName);

protected:
	EventCounterStore();

	typedef HashMapStringToPointer<EventCounter> EventCounterMap;
	EventCounterMap 						     hmEventCounters;

	Mutex mutex;
	friend class Factory<EventCounterStore>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_EC_EventCounterStore_H_ */
