/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/DistributionAgent.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_DistributionAgent_H_
#define _IAS_QS_Workers_Proc_Logic_DistributionAgent_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/DistributionAgent.h>
#include <org/invenireaude/qsystem/workers/io/ProducerOutput.h>


#include "LogicBase.h"

#include <qs/workers/proc/logic/Logic.h>
#include <qs/workers/proc/io/ProducerOutput.h>
#include <org/invenireaude/qsystem/workers/Context.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
/** The DistributionAgent class.
 *
 */
class DistributionAgent : public LogicBase{
public:

	virtual ~DistributionAgent() throw();

protected:
	DistributionAgent(const ::org::invenireaude::qsystem::workers::logic::DistributionAgent* dmParameters,
				  WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							DM::DataObjectPtr& dmData);

	virtual void computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							API::Message* pMessage);

	::org::invenireaude::qsystem::workers::io::Ext::ProducerOutputPtr       dmProducerOutput;

	String strAttribute;

	IO::ProducerOutput* createProducer(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext);

	friend class Factory<DistributionAgent>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_DistributionAgent_H_ */
