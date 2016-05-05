/*
 * File: IAS-QSystemMod-ServiceManager/src/qs/workers/proc/logic/sm/ExplicitExecute.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_ExplicitExecute_H_
#define _IAS_QS_Workers_Proc_Logic_ExplicitExecute_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/External.h>
#include <qs/workers/proc/logic/LogicBase.h>


namespace IAS {

namespace SM {
namespace API{
class ServiceManager;
class ActionDispatcher;
}
}

namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SM{

class Context;
class Execution;

/*************************************************************************/
/** The ExplicitExecute class.
 *
 */
class ExplicitExecute :
		public LogicBase{
public:

	virtual ~ExplicitExecute() throw();

protected:
	ExplicitExecute(const ::org::invenireaude::qsystem::workers::logic::External* dmParameters,
			  	    WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						   DM::DataObjectPtr& dmData);

	virtual void computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								API::Message* pMessage);

	IAS_DFT_FACTORY< ::IAS::SM::API::ServiceManager>::PtrHolder   ptrServiceManager;
	IAS_DFT_FACTORY< ::IAS::SM::API::ActionDispatcher>::PtrHolder ptrActionDispatcher;

	friend class Factory<ExplicitExecute>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_ExplicitExecute_H_ */
