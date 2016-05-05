/*
 * File: LogicStats.h
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


#ifndef _IAS_QS_Workers_Proc_Stats_LogicStats_H_
#define _IAS_QS_Workers_Proc_Stats_LogicStats_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

/*************************************************************************/
/** The LogicStats class.
 *
 */
class LogicStats {
public:

	virtual ~LogicStats() throw();


	void addSuccess(const TimeSample& ts);
	void addFailure(const TimeSample& ts);

	void read(TimeSamplesResults& tsrSuccess, TimeSamplesResults& tsrFailure, bool bReset = false);

protected:
	LogicStats();

	Mutex theMutex;

	TimeSamplesResults tsrSuccess;
	TimeSamplesResults tsrFailure;

	friend class Factory<LogicStats>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Stats_LogicStats_H_ */
