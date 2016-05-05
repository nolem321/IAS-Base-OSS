/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/Queue.h
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
#ifndef _IAS_QS_Queue_Shared_Queue_H_
#define _IAS_QS_Queue_Shared_Queue_H_

#include <commonlib/commonlib.h>
#include "QueueData.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

class MsgEntry;
class Subscription;
class Session;

/*************************************************************************/
/** The Queue class.
 *
 */
class Queue {
public:

	typedef unsigned short int QueueSize;
	typedef short unsigned int ID;

	enum Mode{
		QM_NotAllocated,
		QM_Queue,
		QM_Topic,
		QM_Temporary
	};

	typedef QueueData::Stats Stats;

	Queue();
	~Queue();

	void setupQueue(const String& strName, int iQueueSize);
	void setupTopic(const String& strName, int iQueueSize);
	void setupLink(const String& strName, Queue* pTarget);
	void setupTemporary(int iQueueSize);

	void subscribe(Queue *pTopic, Subscription* pSubscription);
	void unsubscribe();

	Queue* open();
	void close();
	void remove();

	static const int C_MaxQNameLength = 64;

	static const unsigned int C_Unlimited=99999; //TODO limits

	bool put(const MsgEntry& refMsgEntry, unsigned int iWaitTimeMs=C_Unlimited);
	bool get(MsgEntry& refMsgEntry, unsigned int iWaitTimeMs=C_Unlimited);

	typedef QueueSize BrowseLocator;
	static const BrowseLocator C_StartLocation = USHRT_MAX;

	bool browse(MsgEntry& refMsgEntry, BrowseLocator& iLocation, unsigned int iWaitTimeMs=C_Unlimited);

	/*
	 * We need this here since locking is essential.
	 */
	void getAndPublish(unsigned int iWaitTimeMs=C_Unlimited);

	/*
	 * Some utilities.
	 */

	inline bool isAllocated(){
		Mutex::Locker locker(mutex);
		return isAllocatedNoLock();
	 }

	inline Queue *getSubscriptionList() {
		Mutex::Locker locker(mutex);
		if(!pNextSubscriber)
			IAS_THROW(InternalException(String("Subscription list not set: ")+sName));
		return pNextSubscriber;

	}

	inline bool isFree() {
		Mutex::Locker locker(mutex);
		return iMode == QM_NotAllocated;
	 }

	inline bool isType(Mode iMode) {
		Mutex::Locker locker(mutex);
		return this->iMode == iMode;
	 }

	inline String getName(){
		Mutex::Locker locker(mutex);
		return sName;
	};

	inline QueueSize getSize(){
		Mutex::Locker locker(mutex);
		return ptrQueueData->getSize();
	};

	inline QueueSize getNumMsgs(){
		Mutex::Locker locker(mutex);
		return ptrQueueData->getNumMsgs();
	};

	inline long getQueueDataId(){
		return (long)ptrQueueData.operator ->();
	};


	inline void getStats(Stats& _stats, bool bReset=false){
		Mutex::Locker locker(mutex);
		ptrQueueData->getStats(_stats,bReset);
	};

	inline short int getUsageCount(){
		Mutex::Locker locker(mutex);
		return iUsageCount;
	};

	inline bool getRemovePendingState(){
		Mutex::Locker locker(mutex);
		return bRemovePending;
	};

protected:

	char sName[C_MaxQNameLength+1];

	Mutex mutex;
	Mode iMode;

	short int iUsageCount;


	QueueData::Holder ptrQueueData;

	Subscription *pSubscription;

	Queue      *pNextSubscriber;
	Queue      *pPrevSubscriber;

	Queue      *pTopic;

	void setup(const String& strName, Queue::Mode iMode);
	void removeSubscribersNoLock();
	void freeNoLock();
	void setRemovePendingNoLock();
	void unsubscribeNoLock();
	void addSubscriberNoLock(Queue *pSubcriberQueue);


	bool bRemovePending;

	inline bool isAllocatedNoLock(){
		return iMode != QM_NotAllocated;
	 }
};


}
}
}
}

#endif /* _IAS_QS_Queue_QueueShared_H_ */

