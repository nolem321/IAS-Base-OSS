/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSActionExecute.cpp
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
#include "SPSActionExecute.h"

#include<qs/log/sps/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/workers/proc/io/Output.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>

#include "sps/ProcessCache.h"

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include "sps/Helper.h"

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
SPSActionExecute::SPSActionExecute(const ::org::invenireaude::qsystem::workers::sps::SPSActionExecute* dmParameters,
								   WCM::WorkContextManager* pWorkContextManager):
	SPSExecute(dmParameters, pWorkContextManager){
	IAS_TRACER;


}
/*************************************************************************/
SPSActionExecute::~SPSActionExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool SPSActionExecute::setupProcessCacheEntry(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	      	  	  	  	  DM::DataObjectPtr& dmData,
					 	      	  	  	  	  SPS::ProcessCacheEntryPtr& ptrProcessCacheEntry){
	IAS_TRACER;

	String strPID;
	int    iSeq;

	SPS::Helper::RetrieveContext(dmContext,strPID,iSeq);

	try{
		ptrProcessCacheEntry = InstanceFeature<SPS::ProcessCache>::GetInstance()->getEntry(strPID);
	}catch(ItemNotFoundException& e){
		IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"No process found, pid="<<strPID<<", seq="<<iSeq);
		return false;
	}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Found:"<<DM::XML::XMLHelper::Stringify(pWorkContextManager->getGlobalContext()->getDataFactory(),ptrProcessCacheEntry->getProcessInstance()));

	bool bResult = !ptrProcessCacheEntry->isTerminated() && iSeq == ptrProcessCacheEntry->getProcessInstance()->getSeq();

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isInfo(),"Result: "<<bResult);

	return bResult;
}
/*************************************************************************/
}
}
}
}
}
