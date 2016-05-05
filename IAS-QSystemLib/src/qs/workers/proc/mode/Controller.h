/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/Controller.h
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
#ifndef _IAS_QS_Workers_Proc_Mode_Controller_H_
#define _IAS_QS_Workers_Proc_Mode_Controller_H_

#include <commonlib/commonlib.h>

#include "Processor.h"

#include <org/invenireaude/qsystem/workers/spec/Specification.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {

class ModeBase;

/*************************************************************************/
/** The Controller class.
 *
 */
class Controller {
public:

	virtual ~Controller() throw();

	virtual void start();

protected:

	virtual ModeBase *createProcessor(int iLogicIdx)=0;
	Controller(GlobalContext* pGlobalContext);

	GlobalContext* pGlobalContext;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Mode_Controller_H_ */
