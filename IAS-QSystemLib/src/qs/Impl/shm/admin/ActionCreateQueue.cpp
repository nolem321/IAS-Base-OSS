/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/admin/ActionCreateQueue.cpp
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
#include "ActionCreateQueue.h"
#include<qs/log/LogLevel.h>

#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/ActionCreateQueue.h>
#include <org/invenireaude/qsystem/ObjectDefinition.h>
#include <org/invenireaude/qsystem/ObjectName.h>

#include <qs/Impl/shm/Attachment.h>
#include <qs/Impl/shm/shared/QueueTable.h>

using namespace org::invenireaude;

namespace IAS {
namespace QS {
namespace SHM {
namespace Admin {

/*************************************************************************/
ActionCreateQueue::ActionCreateQueue(){
	IAS_TRACER;
}

/*************************************************************************/
ActionCreateQueue::~ActionCreateQueue() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ActionCreateQueue::work(QS::SHM::Attachment *pAttachment, ::org::invenireaude::qsystem::Action* pAction){
	IAS_TRACER;

	const qsystem::Ext::ActionCreateQueuePtr dmCreateQueueAction(qsystem::DataFactory::GetInstance()->getActionCreateQueueType()->cast(pAction));
	String strQueueName=dmCreateQueueAction->getQueueDefinition()->getName();

	int iSize=Shared::QueueTable::C_DftQueueSize;

	if(dmCreateQueueAction->getQueueDefinition()->isSet("size"))
		iSize=dmCreateQueueAction->getQueueDefinition()->getSize();

	Shared::Queue* pQueue=pAttachment->getQueueTable()->createQueue(strQueueName,iSize);

}
/*************************************************************************/
}
}
}
}
