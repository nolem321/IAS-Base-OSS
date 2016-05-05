/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/admin/ActionCreateSubscription.cpp
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
#include "ActionCreateSubscription.h"
#include<qs/log/LogLevel.h>

#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/ActionCreateSubscription.h>
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
ActionCreateSubscription::ActionCreateSubscription(){
	IAS_TRACER;
}

/*************************************************************************/
ActionCreateSubscription::~ActionCreateSubscription() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ActionCreateSubscription::work(QS::SHM::Attachment *pAttachment, ::org::invenireaude::qsystem::Action* pAction){
	IAS_TRACER;

	const qsystem::Ext::ActionCreateSubscriptionPtr dmCreateQueueAction(qsystem::DataFactory::GetInstance()->getActionCreateSubscriptionType()->cast(pAction));

	String strTopicName=dmCreateQueueAction->getTopicName();
	String strQueueName=dmCreateQueueAction->getQueueName();


	Shared::Queue* pTopic=pAttachment->getQueueTable()->lookup(strTopicName);
	Shared::Queue* pQueue=pAttachment->getQueueTable()->lookup(strQueueName);


	pQueue->subscribe(pTopic,NULL);

}
/*************************************************************************/
}
}
}
}
