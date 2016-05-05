/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/ResultHandlerForIO.h
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
#ifndef _IAS_QS_Workers_Proc_Prog_ResultHandlerForIO_H_
#define _IAS_QS_Workers_Proc_Prog_ResultHandlerForIO_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include "ProgramSet.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic{
class LogicBase;
}
namespace Prog {

/*************************************************************************/
/** The ResultHandlerForIO class.
 *
 */
class ResultHandlerForIO : public ProgramSet::ResultHandler{
public:

	virtual ~ResultHandlerForIO() throw();

	void setResultOutput(IO::Output* pResultOutput);
	void setExceptionOutput(IO::Output* pExceptionOutput);

protected:

	ResultHandlerForIO(const ::IAS::DM::DataFactory *pDataFactory,
					   Logic::LogicBase* pLogic) throw();

	Logic::LogicBase* pLogic;

	virtual void handle(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						Lang::Interpreter::Exe::ProgramContext *pProgramContext);

	virtual void handleException(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								 Lang::Interpreter::Exe::ProgramContext *pProgramContext,
								 Lang::Interpreter::Exe::InterpreterProgramException& e);

	const ::IAS::DM::DataFactory *pDataFactory;

	friend class Factory<ResultHandlerForIO>;
};

/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_Prog_ResultHandlerForIO_H_ */
