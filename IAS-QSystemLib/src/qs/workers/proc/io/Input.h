/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/Input.h
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
#ifndef _IAS_QS_Workers_Proc_IO_Input_H_
#define _IAS_QS_Workers_Proc_IO_Input_H_

#include <dm/datamodel.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <qs/api.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {
/*************************************************************************/
/** The Input class.
 *
 */
class Input {
public:

	virtual ~Input() throw(){};

	/*
	 * All in one.
	 */


	static const int CDefaultTimeout = - 2;

	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObjectPtr& dmData,
						 int iTimeout = CDefaultTimeout)=0;

	/*
	 * If you want a raw message to play with.
	 */

	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 API::Message::PtrHolder& ptrMessage,
						 int iTimeout = CDefaultTimeout)=0;

	typedef IAS_DFT_FACTORY<Input>::PtrHolder  PtrHolder;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_Input_H_ */
