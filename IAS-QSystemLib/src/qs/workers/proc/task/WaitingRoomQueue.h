/*
 * File: WaitingRoomQueue.h
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


#ifndef _IAS_QS_Workers_Proc_Task_WaitingRoomQueue_H_
#define _IAS_QS_Workers_Proc_Task_WaitingRoomQueue_H_

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/logic/BackgroundTask.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task {

class BackgroundTask;
class WaitingRoom;
/*************************************************************************/
/** The WaitingRoomQueue class.
 *
 */

class WaitingRoomQueue {
public:

	virtual ~WaitingRoomQueue() throw();

	void addTask(BackgroundTask* pBackgroundTask);
	void removeTask(BackgroundTask* pBackgroundTask);

	void getScheduledData(String& strTaskId, DM::DataObjectPtr& dmDataObject);

	void setTaskSuccess(const String strTaskId,DM::DataObject* dmDataObject);
	void setTaskFailure(const String strTaskId,DM::DataObject* dmDataObject);

	bool getResultData(const String strTaskId, org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& dmDataObject, unsigned int iTimeoutMS);

protected:
	WaitingRoomQueue(const WaitingRoom* pWaitingRoom);

	Mutex mutex;
	Condition cndSchedledReaders;
	Condition cndResultReaders;

	const WaitingRoom* pWaitingRoom;

	typedef HashMapStringToPointer<BackgroundTask>  BackgroundTaskMap;
	typedef std::list<BackgroundTask*>              ScheduledBackgroundTasksList;

	BackgroundTaskMap              hmBackgroundTaskMap;
	ScheduledBackgroundTasksList   lstScheduledBackgroundTasks;

	void checkIfEndOfWork();
	void setTaskStatus(const String strTaskId,DM::DataObject* dmDataObject, bool  bIsSuccess);

    BackgroundTaskMap::iterator getMatch(const String strTaskId);

	friend class Factory<WaitingRoomQueue>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Task_WaitingRoomQueue_H_ */
