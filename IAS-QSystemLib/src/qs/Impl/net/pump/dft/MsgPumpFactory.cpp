/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/dft/MsgPumpFactory.cpp
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
#include "MsgPumpFactory.h"

#include "InputMsgPump.h"
#include "OutputMsgPump.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace Dft {

/*************************************************************************/
MsgPumpFactory::MsgPumpFactory(){
	IAS_TRACER;
}
/*************************************************************************/
MsgPumpFactory::~MsgPumpFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IAS::Net::Async::IDataPump* MsgPumpFactory::createOutputPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage)const{
	IAS_TRACER;
	return IAS_DFT_FACTORY<OutputMsgPump>::Create(pBlockIO,pMessage);
}
/*************************************************************************/
IAS::Net::Async::IDataPump* MsgPumpFactory::createInputPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage)const{
	IAS_TRACER;
	return IAS_DFT_FACTORY<InputMsgPump>::Create(pBlockIO,pMessage);
}
/*************************************************************************/
}
}
}
}
}
