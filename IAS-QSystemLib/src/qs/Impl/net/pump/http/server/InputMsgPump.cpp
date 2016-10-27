/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/server/InputMsgPump.cpp
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
namespace Server {
/*************************************************************************/
InputMsgPump::InputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
			HTTP::InputMsgPump(pBlockIO,pMessage){

	IAS_TRACER;

	ptrRequest   = IAS_DFT_FACTORY< ::IAS::Net::HTTP::Request>::Create();
	ptrInputPump = IAS_DFT_FACTORY< ::IAS::Net::HTTP::HeaderInputPump>::
			Create< ::IAS::Net::HTTP::Request*, IAS::Net::IBlockIO*>(ptrRequest,pBlockIO);

}
/*************************************************************************/
InputMsgPump::~InputMsgPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::Net::HTTP::Header* InputMsgPump::getHeader()const{
	return ptrRequest;
}
/*************************************************************************/
void InputMsgPump::onHeaderReady(){
	IAS_TRACER;

	const String& strValue(ptrRequest->getResource());

	String::size_type iLen=strValue.length();

	API::Attributes* pAttributes = pMessage->getAttributes();

	pAttributes->setValue("IAS_HTML_RESOURCE",strValue);

	if(iLen > 3 && strValue[iLen-1] == 'y' && strValue[iLen-2] == '.')
		pAttributes->setValue("IAS_PROG_NAME",TypeTools::Replace(strValue.substr(0,iLen-2),"/","::"));

	const ::IAS::Net::HTTP::Request::CookiesList& lstCookies(ptrRequest->getCookies());

	for(::IAS::Net::HTTP::Request::CookiesList::const_iterator it=lstCookies.begin(); it != lstCookies.end(); ++it) {
		pAttributes->setValue("IAS_COOKIE_"+(*it).first,(*it).second);
	};

	try{

		const String& strContentType(ptrRequest->getContentType());

		if(strContentType.substr(0,16).compare("application/json")==0)
			pAttributes->setFormat("JSON");
		else if(strContentType.substr(0,15).compare("application/xml")==0)
			pAttributes->setFormat("XML");
		else
			pAttributes->setFormat("String");
	}catch(...){
		pAttributes->setFormat("String");
	}


	if(ptrRequest->isSetAuthorization()){
		String strMethod;
		String strParameter;
		ptrRequest->getAuthoriation(strMethod,strParameter);

		if(strMethod.compare("Basic") == 0){

			String strDecoded;
			MiscTools::Base64ToString(strParameter,strDecoded);
			String::size_type iIdx = strDecoded.find(':');

			if(iIdx != String::npos){
				pAttributes->setValue("IAS_HTTP_AUTH_USER",strDecoded.substr(0,iIdx));
				pAttributes->setValue("IAS_HTTP_AUTH_PASS",strDecoded.substr(iIdx+1));
			}else{
				pAttributes->setValue("IAS_HTTP_AUTH_USER",strDecoded);
			}

		}else if(strMethod.compare("Bearer") == 0){
			pAttributes->setValue("IAS_HTTP_AUTH_BEARER",strParameter);
		}

	}
}
/*************************************************************************/
}
}
}
}
}
}
