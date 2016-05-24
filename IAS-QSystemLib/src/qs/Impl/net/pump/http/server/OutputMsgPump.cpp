/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/server/OutputMsgPump.cpp
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
namespace HTTP {
namespace Server {

/*************************************************************************/
OutputMsgPump::OutputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
	HTTP::OutputMsgPump(pBlockIO,pMessage){
	IAS_TRACER;

	ptrResponse   = IAS_DFT_FACTORY< ::IAS::Net::HTTP::Response>::Create();

	const API::Attributes* pAttributes = pMessage->getAttributes();

	if(pAttributes->isSet("IAS_HTTP_STATUS"))
			ptrResponse->setStatus(static_cast<IAS::Net::HTTP::Response::Status>(
				TypeTools::StringToInt(pAttributes->getValue("IAS_HTTP_STATUS"))));
		else
			ptrResponse->setStatus(::IAS::Net::HTTP::Response::HS_OK);

	//ptrResponse->setTransferEncoding("chunked");

	size_t iDataLength = pMessage->getContent()->tellp();
	ptrResponse->setContentLength(iDataLength);

	const String& strFormat(pMessage->getAttributes()->getFormat());

	if(strFormat[0] == 'J'){
		ptrResponse->setContentType("application/json; charset=UTF-8");
	}else if(strFormat[0] == 'X'){
		ptrResponse->setContentType("application/xml; charset=UTF-8");
	}else{
		ptrResponse->setContentType("application/text; charset=UTF-8");
	}

	if(pAttributes->isSet("IAS_HTTP_SET_COOKIE")){
		ptrResponse->addCookieSpecification(pAttributes->getValue("IAS_HTTP_SET_COOKIE"));
	}
	ptrOutputPump = IAS_DFT_FACTORY< ::IAS::Net::HTTP::HeaderOutputPump>::Create< ::IAS::Net::HTTP::Response*, IAS::Net::IBlockIO* >(ptrResponse,pBlockIO);
}
/*************************************************************************/
OutputMsgPump::~OutputMsgPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::Net::HTTP::Header* OutputMsgPump::getHeader()const{
	return ptrResponse;
}
/*************************************************************************/
}
}
}
}
}
}
