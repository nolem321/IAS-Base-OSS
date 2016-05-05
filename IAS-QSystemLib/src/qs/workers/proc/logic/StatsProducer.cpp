/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/StatsProducer.cpp
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
#include "StatsProducer.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <org/invenireaude/qsystem/stats/SystemStats.h>
#include <org/invenireaude/qsystem/stats/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

#include "../GlobalContext.h"
#include "../ProgramProvider.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
StatsProducer::StatsProducer(const ::org::invenireaude::qsystem::workers::logic::StatsProducer* dmParameters,
							  WCM::WorkContextManager* pWorkContextManager):
		Execute(dmParameters,pWorkContextManager){

	IAS_TRACER;

	this->dmParameter=dmParameters->duplicateStatsProducer();

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getRunList());

	if(lstExeNames.size()){

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++)
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);

	}else{
		ptrProgramSet=0;
	}


}
/*************************************************************************/
StatsProducer::~StatsProducer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatsProducer::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==StatsProducer starts.");


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"StatsProducer for:"<<dmParameter.isNull());

	URI uri;
	API::Administrator *pAdministrator=pWorkContextManager->qs.lookupAdministrator(uri,dmParameter->getConnection());

	stats::Ext::SystemStatsPtr dmStats(pAdministrator->getStats(true));


	if(ptrProgramSet.isNull()){
		getOutput()->send(dmContext,dmStats);
	}else{
		ptrProgramSet->execute(dmContext,dmStats);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==StatsProducer ends.");
}
/*************************************************************************/
}
}
}
}
}
