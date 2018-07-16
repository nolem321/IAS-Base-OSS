/*
 * File: BackgroundTask.h
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


#ifndef _IAS_QS_Workers_Proc_Task_BackgroundTask_H_
#define _IAS_QS_Workers_Proc_Task_BackgroundTask_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/logic/BackgroundTask.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task {

class WaitingRoomQueue;

/*************************************************************************/
/** The BackgroundTask class.
 *
 */
class BackgroundTask {
public:

	virtual ~BackgroundTask() throw();

	void cancel();

	bool isCompleted() const;

	void setParameterCopy(const DM::DataObject* pDataObject);
	void getParameterCopy(DM::DataObjectPtr& ptrDataObject)const;

	void setResult(DM::DataObject* pDataObject);
	void setException(DM::DataObject* pDataObject);

	void getResultAndClear(org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& ptrDataObject);

	inline const String getId()const{
		return dmBackgroundTask->getId();
	}

protected:

	BackgroundTask();

	Mutex mutex;

	org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr dmBackgroundTask;

	void setOwner(WaitingRoomQueue* pWaitingRoomQueue);

	WaitingRoomQueue* pWaitingRoomQueue;

	friend class WaitingRoomQueue;
	friend class Factory<BackgroundTask>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Task_BackgroundTask_H_ */

