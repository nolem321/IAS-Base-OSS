/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/client/OutputMsgPump.cpp
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
namespace Client {

/*************************************************************************/
OutputMsgPump::OutputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
	HTTP::OutputMsgPump(pBlockIO,pMessage){
	IAS_TRACER;

	const API::Attributes* pAttributes = pMessage->getAttributes();

	ptrRequest   = IAS_DFT_FACTORY< ::IAS::Net::HTTP::Request>::Create();

	ptrRequest->setUserAgent("yLib v.1.1");
	ptrRequest->setHost(pMessage->getHost());
	ptrRequest->setAccept("application/json");
	ptrRequest->setAcceptLanguage("en_US");

	if(pAttributes->isSet("IAS_HTTP_METHOD")){

		String strMethod(pAttributes->getValue("IAS_HTTP_METHOD"));

		if(strMethod.compare("GET") == 0){
			ptrRequest->setMethod(IAS::Net::HTTP::Request::HM_GET);
		}else if(strMethod.compare("POST") == 0){
			ptrRequest->setMethod(IAS::Net::HTTP::Request::HM_POST);
		}else if(strMethod.compare("DELETE") == 0){
			ptrRequest->setMethod(IAS::Net::HTTP::Request::HM_DELETE);
		}else{
			IAS_THROW(BadUsageException("Unknown HTTP method."));
		}

	}else{
		ptrRequest->setMethod(IAS::Net::HTTP::Request::HM_POST);
	}

	String strResource(pMessage->getResource());
	if(pAttributes->isSet("IAS_HTTP_URL_PARAM"))
		strResource+=pAttributes->getValue("IAS_HTTP_URL_PARAM");
	ptrRequest->setResource(strResource);

	//ptrRequest->setTransferEncoding("chunked");

	size_t iDataLength = pMessage->getContent()->tellp();
	ptrRequest->setContentLength(iDataLength);


	const String& strFormat(pAttributes->getFormat());

	if(strFormat[0] == 'J'){
		ptrRequest->setContentType("application/json; charset=UTF-8");
	}else if(strFormat[0] == 'X'){
		ptrRequest->setContentType("application/xml; charset=UTF-8");
	}else{

		if(pAttributes->isSet("IAS_HTTP_CONTENT_TYPE"))
			ptrRequest->setContentType(pAttributes->getValue("IAS_HTTP_CONTENT_TYPE"));
		else
			ptrRequest->setContentType("application/text; charset=UTF-8");
	}

	if(pAttributes->isSet("IAS_HTTP_AUTH_USER")){

		String strUser(pAttributes->getValue("IAS_HTTP_AUTH_USER"));
		String strPass(pAttributes->getValue("IAS_HTTP_AUTH_PASS"));

		String strEncoded;

		MiscTools::StringToBase64(strUser + ":" + strPass, strEncoded);
		ptrRequest->setAuthorization("Basic",strEncoded);

	}else if(pAttributes->isSet("IAS_HTTP_AUTH_BEARER")){
		ptrRequest->setAuthorization("Bearer",pAttributes->getValue("IAS_HTTP_AUTH_BEARER"));
	}


	if(pAttributes->isSet("IAS_SOAP_ACTION")){
		ptrRequest->setSOAPAction(pAttributes->getValue("IAS_SOAP_ACTION"));
	}

	ptrOutputPump = IAS_DFT_FACTORY< ::IAS::Net::HTTP::HeaderOutputPump>::Create< ::IAS::Net::HTTP::Request*, IAS::Net::IBlockIO* >(ptrRequest,pBlockIO);
}
/*************************************************************************/
OutputMsgPump::~OutputMsgPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::Net::HTTP::Header* OutputMsgPump::getHeader()const{
	return ptrRequest;
}
/*************************************************************************/
}
}
}
}
}
}
