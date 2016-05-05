/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/RequesterOutput.h
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
#ifndef _IAS_QS_Workers_Proc_IO_RequesterOutput_H_
#define _IAS_QS_Workers_Proc_IO_RequesterOutput_H_

#include <commonlib/commonlib.h>

#include "Output.h"
#include "Input.h"

#include <org/invenireaude/qsystem/workers/io/RequesterOutput.h>

#include <qs/api.h>
#include "Common.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
/** The Output class.
 *
 */
class RequesterOutput : public Common {
public:

	virtual ~RequesterOutput() throw();


	virtual void put(API::Message* pMessage);
	virtual API::Message* get(API::Attributes* pAttributes, int iTimeout);

protected:

	RequesterOutput(const ::org::invenireaude::qsystem::workers::io::RequesterOutput* dmParameter,
			   WCM::WorkContextManager* pWorkContextManager);



	friend class Factory<RequesterOutput>;

	API::Destination inputDestination;
	API::Requester::PtrHolder            ptrRequester;
};

/*************************************************************************/
class RequesterInputProxy : public Input {


	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
						 DM::DataObjectPtr& dmData,
						 int iTimeout);

	virtual void receive(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					     API::Message::PtrHolder& ptrMessage,
						 int iTimeout);

protected:
	RequesterInputProxy(RequesterOutput* pRequester):
		pRequester(pRequester){};

	RequesterOutput* pRequester;

	friend class Factory<RequesterInputProxy>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_IO_RequesterOutput_H_ */

