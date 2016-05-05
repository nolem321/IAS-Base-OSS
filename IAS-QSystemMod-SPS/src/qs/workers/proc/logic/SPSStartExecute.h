/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/SPSStartExecute.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPSStartExecute_H_
#define _IAS_QS_Workers_Proc_Logic_SPSStartExecute_H_

#include <commonlib/commonlib.h>


#include <org/invenireaude/qsystem/workers/sps/SPSStartExecute.h>

#include "SPSExecute.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
/** The SPSStartExecute class.
 *
 */
class SPSStartExecute
		: public SPSExecute{
public:

	virtual ~SPSStartExecute() throw();

protected:
	SPSStartExecute(const ::org::invenireaude::qsystem::workers::sps::SPSStartExecute* dmParameters,
				    WCM::WorkContextManager* pWorkContextManager);

	virtual bool setupProcessCacheEntry(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
		    						    DM::DataObjectPtr& dmData,
		    						    SPS::ProcessCacheEntryPtr& ptrProcessCacheEntry);

	friend class Factory<SPSStartExecute>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPSStartExecute_H_ */
