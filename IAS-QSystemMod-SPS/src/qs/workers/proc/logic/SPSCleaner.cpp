/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSCleaner.cpp
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
#include "SPSCleaner.h"

#include<qs/log/sps/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

#include "sps/ProcessCacheEntry.h"
#include "sps/ProcessCache.h"

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
SPSCleaner::SPSCleaner(const ::org::invenireaude::qsystem::workers::sps::SPSCleaner* dmParameters,
					   WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters,pWorkContextManager){
	IAS_TRACER;

	SPS::ProcessCache::CreateInstanceSafely();

}
/*************************************************************************/
SPSCleaner::~SPSCleaner() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SPSCleaner::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"===== SPSCleaner starts =====");

	SPS::ProcessCache::EntriesList lstEntries;

	InstanceFeature<SPS::ProcessCache>::GetInstance()->getEntriesToClean(lstEntries);

	for(SPS::ProcessCache::EntriesList::iterator it=lstEntries.begin();
		it != lstEntries.end(); it++){

		IAS_CHECK_IF_NULL(*it);
		(*it)->enqueueForSchedule();

		IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"PI:"<<DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),(*it)->getProcessInstance()));

		InstanceFeature<SPS::ProcessCache>::GetInstance()->synchronize(*it);
	}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"== SPSCleaner ends.");
}
/*************************************************************************/
}
}
}
}
}
