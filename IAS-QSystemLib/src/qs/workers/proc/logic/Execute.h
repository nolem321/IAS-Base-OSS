/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/Execute.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_Execute_H_
#define _IAS_QS_Workers_Proc_Logic_Execute_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/logic/Execute.h>

#include <qs/workers/proc/prog/ProgramSet.h>
#include <qs/workers/proc/prog/ResultHandlerForIO.h>

#include "LogicBase.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
/** The Execute class.
 *
 */
class Execute : public LogicBase {
public:

	virtual ~Execute() throw();

protected:
	Execute(const ::org::invenireaude::qsystem::workers::logic::Execute* dmParameters,
			WCM::WorkContextManager* pWorkContextManager);

	IAS_DFT_FACTORY<Prog::ProgramSet>::PtrHolder         ptrProgramSet;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_Execute_H_ */
