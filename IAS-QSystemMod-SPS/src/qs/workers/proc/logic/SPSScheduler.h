/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSScheduler.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPSScheduler_H_
#define _IAS_QS_Workers_Proc_Logic_SPSScheduler_H_

#include <commonlib/commonlib.h>


#include <org/invenireaude/qsystem/workers/sps/SPSScheduler.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>

#include <qs/workers/proc/logic/Execute.h>
#include <qs/workers/proc/logic/LogicBase.h>

#include <lang/interpreter/TypeList.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

namespace SPS{
class ProcessCacheEntry;
}

/*************************************************************************/
/** The SPSScheduler class.
 *
 */
class SPSScheduler :
		public LogicBase{
public:

	virtual ~SPSScheduler() throw();

protected:
	SPSScheduler(const ::org::invenireaude::qsystem::workers::sps::SPSScheduler* dmParameters,
				WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						    DM::DataObjectPtr& dmData);

	ThreadSpecific<SPS::ProcessCacheEntry>::Pointer pProcessCacheEntry;

	unsigned int iMaxPage;
	unsigned int iMaxScheduled;

	friend class Factory<SPSScheduler>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPSScheduler_H_ */
