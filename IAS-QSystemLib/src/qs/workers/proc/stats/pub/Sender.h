/*
 * File: Sender.h
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


#ifndef _IAS_QS_Workers_Proc_Stats_Pub_Sender_H_
#define _IAS_QS_Workers_Proc_Stats_Pub_Sender_H_

#include <commonlib/commonlib.h>

#include "../Publisher.h"

#include <org/invenireaude/qsystem/workers/stats/Sender.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace WCM{
class WorkContextManager;
}
namespace Stats {
namespace Pub {


/*************************************************************************/
/** The Sender class.
 *
 */
class Sender : public Publisher{
public:

	virtual ~Sender() throw();


	virtual void publish(::org::invenireaude::qsystem::workers::stats::LogicSamplesSet* dmLogicSamplesSet,
			::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager)const;

protected:
	Sender( const ::org::invenireaude::qsystem::workers::stats::Sender* dmSender);

	String strOutputName;

	friend class Factory<Sender>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Stats_Pub_Sender_H_ */
