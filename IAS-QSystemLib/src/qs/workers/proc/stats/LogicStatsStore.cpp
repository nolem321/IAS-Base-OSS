/*
 * File: LogicStatsStore.cpp
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

#include "LogicStatsStore.h"

#include "LogicStats.h"

#include <org/invenireaude/qsystem/stats/Sample.h>
#include <org/invenireaude/qsystem/workers/stats/LogicSample.h>
#include <org/invenireaude/qsystem/workers/stats/DataFactory.h>


using namespace ::org::invenireaude;
using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

/*************************************************************************/
LogicStatsStore::LogicStatsStore(){
	IAS_TRACER;
}

/*************************************************************************/
LogicStatsStore::~LogicStatsStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
stats::Ext::LogicSamplesSetPtr LogicStatsStore::getSamples(bool bReset){
	IAS_TRACER;

	Mutex::Locker locker(theMutex);

	stats::Ext::LogicSamplesSetPtr dmResult(stats::DataFactory::GetInstance()->getLogicSamplesSetType()
			->createLogicSamplesSet());


	for(LogicStatsMap::iterator it=hmLogicStatsMap.begin();
		it != hmLogicStatsMap.end(); it++){

		TimeSamplesResults tsrSuccess;
		TimeSamplesResults tsrFailure;

		IAS_CHECK_IF_NULL(it->second);

		it->second->read(tsrSuccess,tsrFailure,bReset);

		stats::LogicSample* dmLogicSample(dmResult->createLogicSample());

		qsystem::stats::Sample *dmSample = dmLogicSample->createSuccess();
		dmSample->setMin(tsrSuccess.iMin/1000);
		dmSample->setMax(tsrSuccess.iMax/1000);
		dmSample->setAvg(tsrSuccess.iNumSamples ? tsrSuccess.iTotal/tsrSuccess.iNumSamples/1000 : 0);
		dmSample->setNum(tsrSuccess.iNumSamples);

		dmSample = dmLogicSample->createFailure();
		dmSample->setMin(tsrFailure.iMin/1000);
		dmSample->setMax(tsrFailure.iMax/1000);
		dmSample->setAvg(tsrFailure.iNumSamples ? tsrFailure.iTotal/tsrFailure.iNumSamples/1000 : 0);
		dmSample->setNum(tsrFailure.iNumSamples);

		dmLogicSample->setName(it->first);
	}

	return dmResult;
}
/*************************************************************************/
LogicStats* LogicStatsStore::createLogicStats(const String& strName){
	IAS_TRACER;

	Mutex::Locker locker(theMutex);

	if(hmLogicStatsMap.count(strName) == 0)
		hmLogicStatsMap[strName]=IAS_DFT_FACTORY<LogicStats>::Create();

	return hmLogicStatsMap[strName];
}
/*************************************************************************/

}
}
}
}
}
