/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/server/MsgPumpFactory.h
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
#ifndef _IAS_QS_Net_Pump_HTTP_Server_MsgPumpFactory_H_
#define _IAS_QS_Net_Pump_HTTP_Server_MsgPumpFactory_H_

#include <commonlib/commonlib.h>

#include "../../MsgPumpFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace HTTP {
namespace Server {

/*************************************************************************/
/** The MsgPumpFactory class.
 *
 */
class MsgPumpFactory : public Pump::MsgPumpFactory{
public:

	virtual ~MsgPumpFactory() throw();

	virtual IAS::Net::Async::IDataPump* createOutputPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage)const;
	virtual IAS::Net::Async::IDataPump* createInputPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage)const;

protected:
	MsgPumpFactory();

	friend class Factory<MsgPumpFactory>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Net_Pump_HTTP_Server_MsgPumpFactory_H_ */
