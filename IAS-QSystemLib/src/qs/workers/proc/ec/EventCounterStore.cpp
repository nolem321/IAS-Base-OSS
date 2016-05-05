/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/EventCounterStore.cpp
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
#include "EventCounterStore.h"
#include <qs/log/LogLevel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {

/*************************************************************************/
EventCounterStore::EventCounterStore(){
	IAS_TRACER;
}
/*************************************************************************/
EventCounterStore::~EventCounterStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void EventCounterStore::addEventCounter(const String& strName, EventCounter* pEventCounter){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmEventCounters.count(strName) > 0)
		IAS_THROW(AlreadyExists(String("cache: ")+strName));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"EC: "<<strName);

	hmEventCounters[strName]=pEventCounter;
}
/*************************************************************************/
EventCounter* EventCounterStore::lookup(const String& strName){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmEventCounters.count(strName) == 0)
		IAS_THROW(ItemNotFoundException(String("event counter: ")+strName));

	return hmEventCounters.at(strName);

}
/*************************************************************************/

}
}
}
}
}
