/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/server/OutputMsgPump.h
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
#ifndef _IAS_QS_Net_Pump_HTTP_Server_OutputMsgPump_H_
#define _IAS_QS_Net_Pump_HTTP_Server_OutputMsgPump_H_

#include <commonlib/commonlib.h>
#include <commonlib/net/http/http.h>

#include "../OutputMsgPump.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace HTTP {
namespace Server {
/*************************************************************************/
/** The OutputMsgPump class.
 *
 */
class OutputMsgPump : public HTTP::OutputMsgPump {
public:

	virtual ~OutputMsgPump() throw();


protected:
	OutputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage);

	virtual ::IAS::Net::HTTP::Header* getHeader()const;

	IAS_DFT_FACTORY< ::IAS::Net::HTTP::Response>::PtrHolder     ptrResponse;

	friend class Factory<OutputMsgPump>;
};

/*************************************************************************/
}
}
}
}
}
}
#endif /* _IAS_QS_Net_Pump_HTTP_Server_OutputMsgPump_H_ */
