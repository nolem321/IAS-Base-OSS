/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/cache/Context.cpp
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
#include "Context.h"

#include <qs/log/LogLevel.h>

#include "../../GlobalContext.h"

#include <qs/workers/proc/task/BackgroundTask.h>
#include <qs/workers/proc/task/WaitingRoom.h>
#include <qs/workers/proc/task/WaitingRoomQueue.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace Task {

/*************************************************************************/
Context::Context(GlobalContext *pGlobalContext)throw():
	pGlobalContext(pGlobalContext){
	IAS_TRACER;
}

/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Context::clear(){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Clearing tasks data ... ");

	for(TaskMap::iterator it = hmTasks.begin();
		it != hmTasks.end(); it++){
		it->second->cancel();
	}
}
/*************************************************************************/
String Context::scheduleBackgroundTask(const String& strWaitingRoom, const DM::DataObject* dm){

	IAS_TRACER;

	IAS_DFT_FACTORY<Proc::Task::BackgroundTask>::PtrHolder ptrBackgroundTask(
		IAS_DFT_FACTORY<Proc::Task::BackgroundTask>::Create()
	);

	ptrBackgroundTask->setParameterCopy(dm);

	String strTaskId(ptrBackgroundTask->getId());

	pGlobalContext->getWaitingRoom()->getQueue(strWaitingRoom)->addTask(ptrBackgroundTask.pass());

	return strTaskId;
}
/*************************************************************************/
bool Context::getBackgroundTaskResult(const String& strWaitingRoom,
										  const String& strTaskId,
										  org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& dmDataObject,
										  unsigned int iTimeoutMS){

	IAS_TRACER;

	return pGlobalContext->getWaitingRoom()->getQueue(strWaitingRoom)->
		    getResultData(strTaskId, dmDataObject, iTimeoutMS);

}
/*************************************************************************/
}
}
}
}
}
}
