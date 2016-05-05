/*
 * File: LogicStats.cpp
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

#include "LogicStats.h"

#include <unistd.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

/*************************************************************************/
LogicStats::LogicStats(){
	IAS_TRACER;
}

/*************************************************************************/
LogicStats::~LogicStats() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void LogicStats::addSuccess(const TimeSample& ts){
	IAS_TRACER;
	Mutex::Locker locker(theMutex);

	tsrSuccess.addSample(ts);

}
/*************************************************************************/
void LogicStats::addFailure(const TimeSample& ts) {
	IAS_TRACER;
	Mutex::Locker locker(theMutex);
	tsrFailure.addSample(ts);
}
/*************************************************************************/
void LogicStats::read(TimeSamplesResults& tsrSuccess, TimeSamplesResults& tsrFailure, bool bReset) {
	IAS_TRACER;

	Mutex::Locker locker(theMutex);

	tsrSuccess = this->tsrSuccess;
	tsrFailure = this->tsrFailure;

	if(bReset){
		this->tsrSuccess.reset();
		this->tsrFailure.reset();
	}
}
/*************************************************************************/

}
}
}
}
}
