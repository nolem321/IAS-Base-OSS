/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/dft/OutputMsgPump.cpp
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
#include "OutputMsgPump.h"

#include <qs/Impl/net/Message.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace Dft {


/*************************************************************************/
OutputMsgPump::OutputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
	pBlockIO(pBlockIO),
	pMessage(pMessage),
	iState(S_Attributes){
	IAS_TRACER;

	pMessage->getBaseAttributes()->write(ssAttributes);

	ptrOutputPump = IAS_DFT_FACTORY< ::IAS::Net::Async::OutputDataPump>::Create< ::IAS::Net::IBlockIO*, std::istream&>(pBlockIO,ssAttributes);
}

/*************************************************************************/
OutputMsgPump::~OutputMsgPump() throw(){
	IAS_TRACER;
	IAS_LOG(true,"output pump deleted: "<<dynamic_cast<void*>(this)<<" net: "<<dynamic_cast<void*>(ptrOutputPump.getPointer()));
}
/*************************************************************************/
::IAS::Net::IBlockIO::Result OutputMsgPump::pump(){
	IAS_TRACER;

	if(!ptrOutputPump)
		return ::IAS::Net::IBlockIO::RC_OK;

	::IAS::Net::IBlockIO::Result rc=ptrOutputPump->pump();

	if(rc != ::IAS::Net::IBlockIO::RC_OK)
		return rc;

	if(iState == S_Content){
		ptrOutputPump=0;
		return ::IAS::Net::IBlockIO::RC_OK;
	}

	iState = S_Content;

	ptrOutputPump = IAS_DFT_FACTORY< ::IAS::Net::Async::OutputDataPump>::Create< ::IAS::Net::IBlockIO*, std::istream&>(pBlockIO,*pMessage->getContent());

	rc=ptrOutputPump->pump();

	if(rc == ::IAS::Net::IBlockIO::RC_OK)
		ptrOutputPump=0;

	return rc;
}
/*************************************************************************/
}
}
}
}
}
