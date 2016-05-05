/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/client/InputMsgPump.cpp
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
#include "InputMsgPump.h"

#include <qs/Impl/net/Message.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace HTTP {
namespace Client {
/*************************************************************************/
InputMsgPump::InputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
		HTTP::InputMsgPump(pBlockIO,pMessage){

	IAS_TRACER;

	ptrResponse   = IAS_DFT_FACTORY< ::IAS::Net::HTTP::Response>::Create();
	ptrInputPump = IAS_DFT_FACTORY< ::IAS::Net::HTTP::HeaderInputPump>::
			Create< ::IAS::Net::HTTP::Response*, IAS::Net::IBlockIO*>(ptrResponse,pBlockIO);

}
/*************************************************************************/
InputMsgPump::~InputMsgPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::Net::HTTP::Header* InputMsgPump::getHeader()const{
	return ptrResponse;
}
/*************************************************************************/
void InputMsgPump::onHeaderReady(){
}
/*************************************************************************/
}
}
}
}
}
}
