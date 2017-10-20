/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/sps/ResultHandlerForIO.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_ResultHandlerForIO_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_ResultHandlerForIO_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/prog/ResultHandlerForIO.h>

#include "ProcessCacheEntry.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic{
class LogicBase;
namespace SPS {

/*************************************************************************/
/** The ResultHandlerForIO class.
 *
 */
class ResultHandlerForIO : public Prog::ResultHandlerForIO{
public:

	virtual ~ResultHandlerForIO() throw();


protected:

	ResultHandlerForIO(const ::IAS::DM::DataFactory *pDataFactory,
						LogicBase* pLogicBase) throw();


	virtual void handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								 Lang::Interpreter::Exe::ProgramContext *pProgramContext,
								 Lang::Interpreter::Exe::InterpreterProgramException& e);

	ThreadSpecific<SPS::ProcessCacheEntry>::Pointer  pProcessCacheEntry;
	ThreadSpecific<WCM::WorkContextManager>::Pointer pWorkContextManager;

	friend class Factory<ResultHandlerForIO>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_Logic_SPS_ResultHandlerForIO_H_ */
