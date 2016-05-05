/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSStartExecute.cpp
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
#include "SPSStartExecute.h"

#include<qs/log/sps/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/workers/proc/io/Output.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>

#include "sps/ProcessCache.h"

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
SPSStartExecute::SPSStartExecute(const ::org::invenireaude::qsystem::workers::sps::SPSStartExecute* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
     SPSExecute(dmParameters, pWorkContextManager){
	IAS_TRACER;

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}

}
/*************************************************************************/
SPSStartExecute::~SPSStartExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool SPSStartExecute::setupProcessCacheEntry(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	      	  	  	  	  DM::DataObjectPtr& dmData,
					 	      	  	  	  	  SPS::ProcessCacheEntryPtr& ptrProcessCacheEntry){
	IAS_TRACER;


	String strProcessName = dmData->getType()->getName();
	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Name="<<strProcessName);
	ptrProcessCacheEntry = InstanceFeature<SPS::ProcessCache>::GetInstance()->createEntry(strProcessName);
	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Found:"<<DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),ptrProcessCacheEntry->getProcessInstance()));

	return true;
}
/*************************************************************************/
}
}
}
}
}
