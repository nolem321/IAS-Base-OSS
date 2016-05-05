/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/QueueTable.h
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
#ifndef _IAS_QS_QueueTable_Shared_QueueTable_H_
#define _IAS_QS_QueueTable_Shared_QueueTable_H_

#include <commonlib/commonlib.h>

#include "Queue.h"

#include <vector>
#include <map>

#include "../System.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

class JournalObjectEntry;
class Session;

/*************************************************************************/
/** The QueueTable class.
 *
 */
class QueueTable {
public:

	static const int C_DftQueueSize=-1;

	Queue*  createQueue(const String& strQName, int iSize = C_DftQueueSize);
	void deleteQueue(const String& strQName);

	Queue*  createLink(const String& strName, const String& strTargetName);

	Queue*  createTopic(const String& strTName, int iSize = C_DftQueueSize);
	void deleteTopic(const String& strTName);

	Queue* createTemporary();

	Queue* lookup(const String& strQName);
	Queue* open(const String& strQName);

	inline long getTopicInfoVersion(){
		return iTopicInfoVersion;
	};

	class Iterator : public std::iterator<std::forward_iterator_tag, Queue*>{
			int iIdx;
			QueueTable  &tab;
			Queue::Mode iMode;

		public:
			Iterator(QueueTable  &tab, Queue::Mode iMode):tab(tab),iIdx(0),iMode(iMode){ skip(); }
			Iterator(QueueTable  &tab):tab(tab),iIdx(tab.iSize),iMode(Queue::QM_NotAllocated){ }
			Iterator(const Iterator& o) : iIdx(o.iIdx),tab(tab),iMode(o.iMode) {}
			Iterator& operator++(){ iIdx++; skip(); return *this; }
			Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
			bool operator==(const Iterator& o) {return iIdx==o.iIdx; }
				bool operator!=(const Iterator& o) {return iIdx!=o.iIdx;}
				Queue* operator*() {return tab.tabQueues+iIdx;}

			private:

			  void skip(){
			   	while(iIdx < tab.iSize && !tab.tabQueues[iIdx].isType(iMode))
			   		iIdx++;
			  }

	};


	inline Iterator begin(Queue::Mode iMode){
		return Iterator(*this,iMode);
	}

	inline Iterator end(){
		return Iterator(*this);
	}

	void setDftQueueSize(int iDftQueueSize);

protected:

	QueueTable(size_t iSize);
	~QueueTable();

	//TODO remove lookupId ?
	Queue* lookupId(Queue::ID id);

	Queue* lookupNoLock(const String& strQName)const;

	Queue* tabQueues;
	friend class Factory<QueueTable>;

	Mutex  mutex;
	size_t iSize;

	long   iTopicInfoVersion;

	Queue* findFreeSlot(const String& strQName);

	TimeSamplesResults tsrLookups;

	int iDftQueueSize;
};

/*************************************************************************/
}
}
}
}

/*
typedef std::vector<Queue, QS::System::SystemAllocator<Queue> > QueueSlots;
//QueueSlots				   tabQueues;

typedef QS::System::SystemAllocator< std::pair<const _HashMapKey, Queue::ID> > QueueNameMapAllocator;

typedef ::std::unordered_map<_HashMapKey,
				 	 	 	 Queue::ID,
				 	 	 	 _HashMapKeyEq,
				 	 	 	  QueueNameMapAllocator> QueueNamesMap;

*/
#endif /* _IAS_QS_QueueTable_QueueTableShared_H_ */
