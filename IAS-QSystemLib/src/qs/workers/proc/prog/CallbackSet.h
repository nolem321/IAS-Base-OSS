/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/CallbackSet.h
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
#ifndef _IAS_QS_Workers_Proc_Prog_CallbackSet_H_
#define _IAS_QS_Workers_Proc_Prog_CallbackSet_H_

#include <commonlib/commonlib.h>
#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Callback.h>
#include <lang/interpreter/exe/ProgramContext.h>
#include "ProgramSet.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class ProgramProvider;
namespace Prog {

/*************************************************************************/
/** The CallbackSet class.
 *
 */
class CallbackSet : public ProgramSet {
public:

	CallbackSet(const ::IAS::DM::DataFactory *pDataFactory):
		ProgramSet(pDataFactory){};

	//ODO result handler ?

	static void Build(ProgramSet      *pProgramSet,
					  ProgramProvider *pProgramProvider,
					  const ::org::invenireaude::qsystem::workers::Ext::CallbackList& lstParamters);

};
/*************************************************************************/
}
}
}
}
}
#endif /* _IAS_QS_Workers_Proc_Prog_CallbackSet_H_ */
