/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/ExplicitExecute.h
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
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS{

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
	ExplicitExecute(::org::invenireaude::qsystem::workers::logic::External* dmParameters,
			  	    WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						   DM::DataObjectPtr& dmData);

	virtual void computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								API::Message* pMessage);

	IAS_DFT_FACTORY<Context>::PtrHolder               ptrContext;
	IAS_DFT_FACTORY<Execution>::PtrHolder             ptrExecution;
	IAS_DFT_FACTORY<DM::JSON::JSONHelper>::PtrHolder ptrJSONHelper;

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
