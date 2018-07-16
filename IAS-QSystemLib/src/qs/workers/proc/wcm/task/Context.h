/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/cache/Context.h
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
#ifndef _IAS_QS_Workers_Proc_WCM_Task_Context_H_
#define _IAS_QS_Workers_Proc_WCM_Task_Context_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/BackgroundTask.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace Task{
class BackgroundTask;
}
namespace WCM {
namespace Task {

/*************************************************************************/
/** The Context class.
 *
 */
class Context {
public:


	Context(GlobalContext *pGlobalContext) throw();
	~Context() throw();

	String scheduleBackgroundTask(const String& strWaitingRoom, const DM::DataObject* dm);
	bool getBackgroundTaskResult(const String& strWaitingRoom,
									const String& strTaskId,
									org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& dmDataObject,
									unsigned int iTimeoutMS);
	void clear();

	protected:

	GlobalContext *pGlobalContext;

	typedef HashMapWithStringKey<Proc::Task::BackgroundTask*> TaskMap;

	TaskMap hmTasks;

};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_WCM_Cache_Context_H_ */
