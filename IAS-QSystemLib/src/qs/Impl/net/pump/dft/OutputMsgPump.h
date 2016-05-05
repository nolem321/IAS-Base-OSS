/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/dft/OutputMsgPump.h
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
#ifndef _IAS_QS_Net_Pump_Dft_OutputMsgPump_H_
#define _IAS_QS_Net_Pump_Dft_OutputMsgPump_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace Net {
class Message;
namespace Pump {
namespace Dft {
/*************************************************************************/
/** The OutputMsgPump class.
 *
 */
class OutputMsgPump : public virtual ::IAS::Net::Async::IDataPump{
public:

	virtual ~OutputMsgPump() throw();

	virtual ::IAS::Net::IBlockIO::Result pump();

	OutputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage);

protected:

	::IAS::Net::IBlockIO* pBlockIO;
	Message*        pMessage;

	enum State{
		S_Attributes,
		S_Content
	};

	State iState;

	StringStream ssAttributes;

	IAS_DFT_FACTORY< ::IAS::Net::Async::OutputDataPump>::PtrHolder ptrOutputPump;

	friend class Factory<OutputMsgPump>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Net_Pump_Dft_OutputMsgPump_H_ */
