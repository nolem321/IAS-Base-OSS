/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/SessionTable.h
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
#ifndef _IAS_QS_SessionTable_Shared_SessionTable_H_
#define _IAS_QS_SessionTable_Shared_SessionTable_H_

#include <commonlib/commonlib.h>

#include "Session.h"

#include "../System.h"

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {

/*************************************************************************/
/** The SessionTable class.
 *
 */
class SessionTable {
public:

	static const int C_DftQueueSize=-1;

	~SessionTable();

	Session*  createTransacted();
	Session*  createAutoCommit();

	class Iterator : public std::iterator<std::forward_iterator_tag, Session*>{
			int iIdx;
			SessionTable  &tab;

		public:
			Iterator(SessionTable  &tab):tab(tab),iIdx(0){ skip(); }
			Iterator(SessionTable  &tab,int iIdx):tab(tab),iIdx(iIdx){ }
			Iterator(const Iterator& o) : iIdx(o.iIdx),tab(tab){}
			Iterator& operator++(){ iIdx++; skip(); return *this; }
			Iterator operator++(int) {Iterator tmp(*this); operator++(); return tmp;}
			bool operator==(const Iterator& o) {return iIdx==o.iIdx; }
				bool operator!=(const Iterator& o) {return iIdx!=o.iIdx;}
				Session* operator*() {return tab.tabSessions+iIdx;}

			private:

			  void skip(){
			   	while(iIdx < tab.iSize && tab.tabSessions[iIdx].isFree())
			   		iIdx++;
			  }

	};


	inline Iterator begin(){
		return Iterator(*this);
	}

	inline Iterator end(){
		return Iterator(*this,iSize);
	}

	void setMaxObjects(unsigned short iMaxObjects);
	void setRollbackSegment(unsigned short iRollbackSegment);

	inline unsigned short getMaxObjects()const { return iMaxObjects; };
	inline unsigned short getRollbackSegment()const { return iRollbackSegment;};

	short int getNumActiveSessions();

protected:

	SessionTable(size_t iSize);

	Session* tabSessions;
	friend class Factory<SessionTable>;

	Mutex  mutex;
	size_t iSize;

	unsigned short iMaxObjects;
	unsigned short iRollbackSegment;

	Session* findFreeSlotNoLock();

	TimeSamplesResults tsrLookups;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_SessionTable_SessionTableShared_H_ */
