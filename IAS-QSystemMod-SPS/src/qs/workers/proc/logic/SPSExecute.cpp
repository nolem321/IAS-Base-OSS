/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSExecute.cpp
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
#include "SPSExecute.h"

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
SPSExecute::SPSExecute(const ::org::invenireaude::qsystem::workers::sps::SPSExecute* dmParameters,
					   WCM::WorkContextManager* pWorkContextManager):
	iMaxSteps(1),
	Execute(dmParameters, pWorkContextManager){
	IAS_TRACER;

	SPS::ProcessCache::CreateInstanceSafely();

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){

		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}

	if(dmParameters->isSetMaxSteps())
		iMaxSteps=dmParameters->getMaxSteps();

}
/*************************************************************************/
SPSExecute::~SPSExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
String SPSExecute::getProgramName(sps::ProcessInstance* pProcessInstance) {
	IAS_TRACER;
	StringStream ssProgramName;

	ssProgramName << "sps::process::" << pProcessInstance->getName() << "::";

	if(pProcessInstance->isSetVer())
		ssProgramName<< pProcessInstance->getVer() << "::";

	ssProgramName<<pProcessInstance->getActivity();

	return ssProgramName.str();
}
/*************************************************************************/
void SPSExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"==== >> SPSExecute starts << ====");

	SPS::ProcessCacheEntryPtr ptrProcessCacheEntry;

	if(setupProcessCacheEntry(dmContext,dmData,ptrProcessCacheEntry)) {

		IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Successful setup - executing...");

		pProcessCacheEntry=ptrProcessCacheEntry;

		sps::ProcessInstance* pProcessInstance = ptrProcessCacheEntry->getProcessInstance();

		int iStepsLeft = iMaxSteps; //TODO default 1 for starter.

		do {

			IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"iStepsLeft = "<<iStepsLeft);

			String strProgram = getProgramName(pProcessInstance);

			ptrProcessCacheEntry->decNumPending();
			ptrProgramSet->execute(strProgram,dmContext,dmData);

			if(ptrProcessCacheEntry->getNumPending() == 0)
				ptrProcessCacheEntry->step();

		}while(!ptrProcessCacheEntry->isTerminated() &&
				--iStepsLeft > 0 && ptrProcessCacheEntry->getNumPending() == 0);

		if(!ptrProcessCacheEntry->isTerminated()) {

			if(ptrProcessCacheEntry->getNumPending() > 0)
				ptrProcessCacheEntry->enqueueForEvent();
			else
				ptrProcessCacheEntry->enqueueForSchedule();
		}


		IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Synchronizing:"<<DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),ptrProcessCacheEntry->getProcessInstance()));

		InstanceFeature<SPS::ProcessCache>::GetInstance()->synchronize(ptrProcessCacheEntry);
		InstanceFeature<SPS::ProcessCache>::GetInstance()->returnToCache(ptrProcessCacheEntry);
	}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"== SPSExecute ends.");
}
/*************************************************************************/
}
}
}
}
}
