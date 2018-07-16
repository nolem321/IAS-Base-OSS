/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/TaskPool.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_TaskPool_H_
#define _IAS_QS_Workers_Proc_Logic_TaskPool_H_

#include <commonlib/commonlib.h>


#include <org/invenireaude/qsystem/workers/logic/TaskPool.h>

#include "Execute.h"

#include <lang/interpreter/TypeList.h>
#include <qs/workers/proc/prog/ProgramSet.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Task{
class WaitingRoomQueue;
}
namespace Logic {

/*************************************************************************/
/** The TaskPool class.
 *
 */
class TaskPool :
		public LogicBase{
public:

	virtual ~TaskPool() throw();

	virtual void compute();
	virtual void receive(bool bNoWait);

protected:
	TaskPool(const ::org::invenireaude::qsystem::workers::logic::TaskPool* dmParameters,
			  	    WCM::WorkContextManager* pWorkContextManager);

	virtual void computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						   DM::DataObjectPtr& dmData);

	String strWaitingRoomQueue;
	Task::WaitingRoomQueue* pWaitingRoomQueue;

	IAS_DFT_FACTORY<Prog::ProgramSet>::PtrHolder         ptrProgramSet;

	org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext;
	DM::DataObjectPtr dmData;

	class ResultHandler : public Prog::ProgramSet::ResultHandler{
	public:

		virtual ~ResultHandler() throw();

	protected:

		ResultHandler(Task::WaitingRoomQueue* pWaitingRoomQueue) throw();

		virtual void handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							Lang::Interpreter::Exe::ProgramContext *pProgramContext);

		virtual void handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
									 Lang::Interpreter::Exe::ProgramContext *pProgramContext,
									 Lang::Interpreter::Exe::InterpreterProgramException& e);

		Task::WaitingRoomQueue* pWaitingRoomQueue;

		friend class Factory<ResultHandler>;
	};


	friend class Factory<TaskPool>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_TaskPool_H_ */
