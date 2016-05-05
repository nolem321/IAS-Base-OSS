/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/SharedBrowserInput.h
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
#ifndef _IAS_QS_Workers_Proc_IO_SharedBrowserInput_H_
#define _IAS_QS_Workers_Proc_IO_SharedBrowserInput_H_

#include <commonlib/commonlib.h>

#include "Input.h"

#include <org/invenireaude/qsystem/workers/io/SharedBrowserInput.h>

#include <qs/api.h>

#include "Common.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {
class SharedBrowserWorker;
/*************************************************************************/
/** The SharedBrowserInput class.
 *
 */
class SharedBrowserInput :
		public Common{
public:

	virtual ~SharedBrowserInput() throw();

	virtual API::Message* get(API::Attributes* pAttributes, int iTimeout);

protected:

	SharedBrowserInput(const ::org::invenireaude::qsystem::workers::io::SharedBrowserInput* dmParameter,
					   WCM::WorkContextManager* pWorkContextManager);


	typedef HashMapStringToPointer<SharedBrowserWorker> WorkersMap;

	struct Workers{
		Workers(bool){};
		WorkersMap                                          hmWorkersMap;
		Mutex												mutex;
	};

	static Workers TheWorkers;

	SharedBrowserWorker* pWorker;

	friend class Factory<SharedBrowserInput>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_SharedBrowserInput_H_ */

