/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/admin/ActionDispatcher.cpp
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
#include "ActionDispatcher.h"
#include<qs/log/LogLevel.h>

#include "ActionWorker.h"
#include "ActionCreateQueue.h"
#include "ActionCreateLink.h"
#include "ActionCreateTopic.h"
#include "ActionDeleteQueue.h"
#include "ActionDeleteTopic.h"
#include "ActionCreateSubscription.h"
#include "ActionRemoveSubscription.h"

#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/Action.h>
#include <org/invenireaude/qsystem/ActionCreateQueue.h>
#include <org/invenireaude/qsystem/ActionCreateLink.h>
#include <org/invenireaude/qsystem/ActionCreateTopic.h>
#include <org/invenireaude/qsystem/ActionDeleteQueue.h>
#include <org/invenireaude/qsystem/ActionDeleteTopic.h>
#include <org/invenireaude/qsystem/ActionCreateSubscription.h>
#include <org/invenireaude/qsystem/ActionRemoveSubscription.h>


using namespace org::invenireaude;

namespace IAS {
namespace QS {
namespace SHM {
namespace Admin {

/*************************************************************************/
ActionDispatcher::ActionDispatcher(QS::SHM::Attachment *pAttachment):pAttachment(pAttachment){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAttachment);

	const DM::Type* pType=qsystem::DataFactory::GetInstance()->getActionCreateQueueType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionCreateQueue>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionCreateLinkType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionCreateLink>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionCreateTopicType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionCreateTopic>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionDeleteQueueType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionDeleteQueue>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionDeleteTopicType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionDeleteTopic>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionCreateSubscriptionType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionCreateSubscription>::Create();

	pType=qsystem::DataFactory::GetInstance()->getActionRemoveSubscriptionType();
	hmActions[pType]=IAS_DFT_FACTORY<ActionRemoveSubscription>::Create();

}
/*************************************************************************/
ActionDispatcher::~ActionDispatcher() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ActionDispatcher::dispatchWork(::org::invenireaude::qsystem::Ext::ActionList& lstActions){
	IAS_TRACER;

	for(int iIdx=0;iIdx<lstActions.size();iIdx++){
		getActionWorker(lstActions.at(iIdx)->getType())->work(pAttachment,lstActions.at(iIdx));
	}
}
/*************************************************************************/
ActionWorker* ActionDispatcher::getActionWorker(const DM::Type* pType){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pType);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Type:"<<pType->getName());

	if(hmActions.count(pType) == 0)
		IAS_THROW(ItemNotFoundException(pType->getName()+"Action worker not found."));

	return hmActions.at(pType);
}
/*************************************************************************/
}
}
}
}

