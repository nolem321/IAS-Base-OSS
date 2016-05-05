/*
 * File: LogicStatsStore.h
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


#ifndef _IAS_QS_Workers_Proc_Stats_LogicStatsStore_H_
#define _IAS_QS_Workers_Proc_Stats_LogicStatsStore_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/stats/LogicSamplesSet.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

class LogicStats;

/*************************************************************************/
/** The LogicStatsStore class.
 *
 */
class LogicStatsStore {
public:

	virtual ~LogicStatsStore() throw();

	::org::invenireaude::qsystem::workers::stats::Ext::LogicSamplesSetPtr getSamples(bool bReset);

	LogicStats* createLogicStats(const String& strName);

protected:
	LogicStatsStore();

	Mutex theMutex;

	typedef HashMapStringToPointer<LogicStats> LogicStatsMap;
	LogicStatsMap							   hmLogicStatsMap;

	friend class Factory<LogicStatsStore>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Stats_LogicStatsStore_H_ */
