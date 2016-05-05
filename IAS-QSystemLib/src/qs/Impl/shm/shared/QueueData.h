/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/QueueData.h
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
#ifndef _IAS_QS_QueueData_Shared_QueueData_H_
#define _IAS_QS_QueueData_Shared_QueueData_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
class MsgEntry;

/*************************************************************************/
/** The QueueData class.
 *
 */
class QueueData {
public:

	typedef unsigned short int QueueDataSize;
	typedef QueueDataSize BrowseLocator;
	static const BrowseLocator C_StartLocation = ~0 /*TODO eclipse indexing problem USHRT_MAX*/;

	struct Stats{

		TimeSamplesResults tsrPut;
		TimeSamplesResults tsrGet;
		TimeSamplesResults tsrBrowse;

		QueueDataSize iMaxNumMsgs;

		TimeSamplesResults tsrMutexWait;


		void reset(QueueDataSize iMaxNumMsgs);
	};

	QueueData();
	~QueueData();

	void setup(QueueDataSize iQueueSize);

	bool put(const MsgEntry& refMsgEntry, unsigned int iWaitTimeMs);
	bool get(MsgEntry& refMsgEntry, unsigned int iWaitTimeMs);
	bool browse(MsgEntry& refMsgEntry, BrowseLocator& iLocation, unsigned int iWaitTimeMs);

	void setRemovePending();
	/*
	 * We need this here since locking is essential.
	 */
	void getAndPublish(unsigned int iWaitTimeMs);

	class Holder{
		public:

			Holder(QueueData* pQueueData = 0){
				assign(pQueueData);
			}

			~Holder(){	dispose(); }

			bool operator!()const { return pQueueData == NULL; }

			QueueData* operator=(QueueData *pQueueData){ assign(pQueueData); return pQueueData;}

			inline QueueData* operator->(){
				IAS_CHECK_IF_NULL(pQueueData);
				return pQueueData;
			};

			void setDeletePending();

		private:

			QueueData      *pQueueData;

			void assign(QueueData   *pQueueData);
			void dispose();

		};


	inline QueueDataSize getNumMsgs(){
		Mutex::Locker locker(mutex);
		return iNumMsgs;
	};

	inline void getStats(Stats& _stats,bool bReset=false){

		Mutex::Locker locker(mutex);
		_stats=*const_cast<Stats*>(&stats);

		if(bReset)
			stats.reset(iNumMsgs);
	};


	inline QueueDataSize getSize(){
		Mutex::Locker locker(mutex);
		return iQueueDataSize;
	};


	static QueueData* Create(QueueDataSize iSize);

protected:

	QueueDataSize iQueueDataSize;

	Mutex mutex;

	Condition cndWriter;
	Condition cndReader;

	short int iRefCount;

	MsgEntry *tabEntries;

	QueueDataSize iHead;
	QueueDataSize iNumMsgs;

	//TODO to some bitmasks or an options class.
	bool bOverwriteOnQFull;
	bool bRemovePending;
	Stats stats;//TODO ??volatile ??
};


}
}
}
}

#endif /* _IAS_QS_QueueData_QueueDataShared_H_ */

