/*
 * File: BackgroundTask.cpp
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

#include "BackgroundTask.h"

#include "WaitingRoomQueue.h"

#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task {


/*************************************************************************/
BackgroundTask::BackgroundTask():

	pWaitingRoomQueue(NULL){
	IAS_TRACER;

	dmBackgroundTask = org::invenireaude::qsystem::workers::logic::DataFactory::GetInstance()->getBackgroundTaskType()->createBackgroundTask();


	static Mutex mutexId;
	static int   jobId = 0;
	{
		Mutex::Locker locker(mutexId);
		dmBackgroundTask->setId(TypeTools::IntToString(++jobId));
	}

	dmBackgroundTask->setScheduledOn(Timestamp(true));

}
/*************************************************************************/
BackgroundTask::~BackgroundTask() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void BackgroundTask::cancel(){

	if(pWaitingRoomQueue)
		pWaitingRoomQueue->removeTask(this);

}
/*************************************************************************/
void BackgroundTask::setParameterCopy(const DM::DataObject* pDataObject){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(!pDataObject)
		this->dmBackgroundTask->unsetParameters();
	else
		this->dmBackgroundTask->setParameters(pDataObject->duplicate());

}
/*************************************************************************/
void BackgroundTask::getParameterCopy(DM::DataObjectPtr& ptrDataObject)const{

	IAS_TRACER;

	Mutex::Locker locker(const_cast<BackgroundTask*>(this)->mutex);

	if(this->dmBackgroundTask->isSetParameters()){

		const DM::DataObject *dmParameters = this->dmBackgroundTask->getParameters();

		if(dmParameters)
			ptrDataObject=dmParameters->duplicate();
		else
			ptrDataObject.unset();

	}else{
		ptrDataObject.unset();
	}

}
/*************************************************************************/
void BackgroundTask::setResult(DM::DataObject* pDataObject){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	dmBackgroundTask->setCompletedOn(Timestamp(true));

	if(!pDataObject)
		this->dmBackgroundTask->unsetResult();
	else
		this->dmBackgroundTask->setResult(pDataObject);

}
/*************************************************************************/
void BackgroundTask::setException(DM::DataObject* pDataObject){

	IAS_TRACER;

	Mutex::Locker locker(mutex);

	dmBackgroundTask->setCompletedOn(Timestamp(true));

	if(!pDataObject)
		this->dmBackgroundTask->unsetException();
	else
		this->dmBackgroundTask->setException(pDataObject);

}
/*************************************************************************/
void BackgroundTask::getResultAndClear(org::invenireaude::qsystem::workers::logic::Ext::BackgroundTaskPtr& ptrDataObject){

	IAS_TRACER;

	Mutex::Locker locker(const_cast<BackgroundTask*>(this)->mutex);

	ptrDataObject = dmBackgroundTask;

	dmBackgroundTask = NULL;
}
/*************************************************************************/
bool BackgroundTask::isCompleted() const{
	IAS_TRACER;

	Mutex::Locker locker(const_cast<BackgroundTask*>(this)->mutex);

	return dmBackgroundTask->isSetCompletedOn();
}
/*************************************************************************/
void BackgroundTask::setOwner(WaitingRoomQueue* pWaitingRoomQueue){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	this->pWaitingRoomQueue = pWaitingRoomQueue;
}
/*************************************************************************/
}
}
}
}
}
