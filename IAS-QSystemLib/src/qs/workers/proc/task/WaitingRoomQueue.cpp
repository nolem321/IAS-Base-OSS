/*
 * File: WaitingRoomQueue.cpp
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

#include "WaitingRoomQueue.h"

#include "BackgroundTask.h"

#include "WaitingRoom.h"

#include "../GlobalContext.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task {

/*************************************************************************/
WaitingRoomQueue::WaitingRoomQueue(const WaitingRoom* pWaitingRoom):
	pWaitingRoom(pWaitingRoom){
	IAS_TRACER;
}

/*************************************************************************/
WaitingRoomQueue::~WaitingRoomQueue() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void WaitingRoomQueue::addTask(BackgroundTask* pBackgroundTask){
	IAS_TRACER;
	Mutex::Locker locker(mutex);

	hmBackgroundTaskMap[pBackgroundTask->getId()] = pBackgroundTask;
	lstScheduledBackgroundTasks.push_back(pBackgroundTask);

	pBackgroundTask->setOwner(this);

	cndSchedledReaders.broadcast();
}
/*************************************************************************/
void WaitingRoomQueue::getScheduledData(String& strTaskId, DM::DataObjectPtr& dmDataObject){

	IAS_TRACER;
	Mutex::Locker locker(mutex);

	ScheduledBackgroundTasksList::iterator it = lstScheduledBackgroundTasks.begin();

	while(it == lstScheduledBackgroundTasks.end()){

		checkIfEndOfWork();

		{
			Thread::Cancellation tc(true);
			mutex.wait(cndSchedledReaders, 2000);
		}

		it = lstScheduledBackgroundTasks.begin();
	}

	strTaskId = (*it)->getId();
	(*it)->getParameterCopy(dmDataObject);

	lstScheduledBackgroundTasks.erase(it);

}
/*************************************************************************/
void WaitingRoomQueue::setTaskSuccess(const String strTaskId, DM::DataObject* dmDataObject){
	IAS_TRACER;
	setTaskStatus(strTaskId, dmDataObject, true);
}
/*************************************************************************/
void WaitingRoomQueue::setTaskFailure(const String strTaskId, DM::DataObject* dmDataObject){
	IAS_TRACER;
	setTaskStatus(strTaskId, dmDataObject, false);
}
/*************************************************************************/
void WaitingRoomQueue::setTaskStatus(const String strTaskId, DM::DataObject* dmDataObject, bool  bIsSuccess){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	BackgroundTaskMap::iterator it = hmBackgroundTaskMap.find(strTaskId);

	if(it == hmBackgroundTaskMap.end())
		return;

	if(bIsSuccess)
		it->second->setResult(dmDataObject);
	else
		it->second->setException(dmDataObject);

	IAS_LOG(true, "Task ready: "<<it->first);
	cndResultReaders.broadcast();
}
/*************************************************************************/
WaitingRoomQueue::BackgroundTaskMap::iterator WaitingRoomQueue::getMatch(const String strTaskId){

	if(!strTaskId.empty()){
		return hmBackgroundTaskMap.find(strTaskId);
	}

	for(BackgroundTaskMap::iterator it = hmBackgroundTaskMap.begin();
		it != hmBackgroundTaskMap.end();
		it++)
		if(it->second->isCompleted())
			return it;

	return hmBackgroundTaskMap.end();

}
/*************************************************************************/
bool WaitingRoomQueue::getResultData(const String strTaskId,
									org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& dmDataObject,
									unsigned int iTimeoutMS){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	BackgroundTaskMap::iterator it = getMatch(strTaskId);


	unsigned int iStartTime = TypeTools::GetTimeMS();

	while(it == hmBackgroundTaskMap.end() || !it->second->isCompleted() ){

		{
			Thread::Cancellation tc(true);

			if(!mutex.wait(cndResultReaders, iTimeoutMS))
				return false;
		}

		iTimeoutMS -= TypeTools::GetTimeMS() - iStartTime;

		it = getMatch(strTaskId);
	}

	it->second->getResultAndClear(dmDataObject);
	hmBackgroundTaskMap.erase(it);
	return true;
}
/*************************************************************************/
void WaitingRoomQueue::removeTask(BackgroundTask* pBackgroundTask){

	IAS_TRACER;
	Mutex::Locker locker(mutex);

	lstScheduledBackgroundTasks.remove(pBackgroundTask);
	hmBackgroundTaskMap.erase(pBackgroundTask->getId());
}
/*************************************************************************/
void WaitingRoomQueue::checkIfEndOfWork(){

	if( pWaitingRoom->getGlobalContext()->isAborted() ||
			SYS::Signal::GetInstance()->isStopping()){

		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Task pool shutdowns.");

		IAS_THROW(EndOfDataException());
	}

}
/*************************************************************************/
}
}
}
}
}
