/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/BrowserInput.h
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
#ifndef _IAS_QS_Workers_Proc_IO_BrowserInput_H_
#define _IAS_QS_Workers_Proc_IO_BrowserInput_H_

#include <commonlib/commonlib.h>

#include "Input.h"

#include <org/invenireaude/qsystem/workers/io/BrowserInput.h>

#include <qs/api.h>
#include "Common.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
/** The BrowserInput class.
 *
 */
class BrowserInput : public Common {
public:

	virtual ~BrowserInput() throw();

	unsigned int skip(unsigned int iOffset);

protected:

	BrowserInput(const ::org::invenireaude::qsystem::workers::io::BrowserInput* dmParameter,
			     WCM::WorkContextManager* pWorkContextManager);

	virtual API::Message* get(API::Attributes* pAttributes, int iTimeout);

	API::Browser::PtrHolder            ptrBrowser;

	enum RecycleMode{
		RM_Never,
		RM_Next,
		RM_Immediate,
		RM_Always,
	};

	RecycleMode iRecycleMode;

	static RecycleMode StringToRecycleMode(const String& strValue);

	friend class Factory<BrowserInput>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_BrowserInput_H_ */

