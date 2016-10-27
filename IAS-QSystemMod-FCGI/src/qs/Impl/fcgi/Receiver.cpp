/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/Receiver.cpp
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
#include "Receiver.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Message.h"
#include "Session.h"
#include "Connection.h"
#include "System.h"
#include <set>
#include <commonlib/commonlib.h>
#include <unistd.h>
namespace IAS {
namespace QS {
namespace FCGI {
/*************************************************************************/
class EligibleAttributesMap : public std::set<String>,
			public IAS::InstanceFeature<EligibleAttributesMap>{
	public:
	EligibleAttributesMap(){

	  Mutex::Locker locker(mutex);

      //insert("HTTP_DNT");
	  //insert("HTTP_USER_AGENT");
	  //insert("HTTP_ACCEPT_ENCODING");
	  insert("QUERY_STRING");
	  //insert("SERVER_PORT");
	  //insert("SERVER_PROTOCOL");
	  insert("SCRIPT_FILENAME");
	  insert("SERVER_ADDR");
	  insert("REQUEST_URI");
	  insert("REQUEST_METHOD");
	  insert("REMOTE_PORT");
	  //insert("DOCUMENT_ROOT");
	  //insert("PATH_INFO");
	  insert("SCRIPT_NAME");
	  //insert("SERVER_SOFTWARE");
	  insert("REMOTE_ADDR");
	  insert("SERVER_NAME");
	  insert("REDIRECT_STATUS");
	  //insert("HTTP_HOST");
	  //insert("GATEWAY_INTERFACE");
	  insert("HTTP_ACCEPT");
	  //insert("HTTP_ACCEPT_LANGUAGE");
	  //insert("HTTP_CONNECTION");
	}

	bool isEligible(const String& strValue) const{
		return true;
		return count(strValue);
	}

protected:
	Mutex mutex;
};
/*************************************************************************/
Receiver::Receiver(Session* pSession):
	Manageable(pSession),
	iCounter(0),
	myDestination("__FAKE__"){
	IAS_TRACER;

	Mutex mutex;
	Mutex::Locker locker(mutex);
	const EligibleAttributesMap* hmEligibleAttributes = EligibleAttributesMap::GetInstance();
}

/*************************************************************************/
Receiver::~Receiver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Receiver::open(const API::Destination& refDestination){
	IAS_TRACER;

}
/*************************************************************************/
API::Message* Receiver::receive(int iTimeWait, API::Attributes* pSelector){

	IAS_TRACER;

	//TODO (M) Separate module !

	Session *pSession=getSession();
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Accepting: ");
	pSession->accept();

	FCGX_Request *pRequest=pSession->getRequest();
	char **env = pRequest->envp;

    String strName;
    String strValue;

    IAS_DFT_FACTORY<Message>::PtrHolder ptrMessage;

    if(FCGX_GetParam("CONTENT_LENGTH",env) != NULL){
    	ptrMessage=IAS_DFT_FACTORY<Message>::Create(pRequest->in);
    }else{
    	ptrMessage=IAS_DFT_FACTORY<Message>::Create();
    }

    API::Attributes* pAttributes=ptrMessage->getAttributes();

    const EligibleAttributesMap* hmEligibleAttributes = EligibleAttributesMap::GetInstance();
    while (*(++env)){
	        String strTmp(*env);
	        TypeTools::ChopArguments(strTmp,strName,strValue);

	        if(hmEligibleAttributes->isEligible(strName))
	        	pAttributes->setValue(strName,strValue);

	        //TODO (M) Faster and nicer
	        if(strName.compare("SCRIPT_NAME")==0){

	        	String strProgramName;
	        	strProgramName=TypeTools::Replace(strValue.substr(1),"/","::");
	        	strProgramName=TypeTools::Replace(strProgramName,".yyy","");
	        	pAttributes->setValue("IAS_PROG_NAME",strProgramName);

	        }else if(strName.compare("HTTP_COOKIE")==0){
	        	parseCookies(strValue,pAttributes);
	        }

	   }/* while */


    //TODO (M) format
    StringStream ssMID;
    ssMID<<"FCGI"<<getSession()->getRequest()->requestId<<"_"<<iCounter++<<"_"<<getpid();
    pAttributes->setMID(ssMID.str());
	pAttributes->setFormat("JSON");
	pAttributes->setReplyTo("_fake_");
	return ptrMessage.pass();
}
/*************************************************************************/
const String& Receiver::CCookiePrefix="IAS_COOKIE_";

void Receiver::parseCookies(const String& strValue, API::Attributes*pAttributes){

	IAS_TRACER;

	String strAttrName;
	String strAttrValue;
	strAttrName.reserve(64);
	strAttrValue.reserve(128);
	bool bName = true;

	//TODO (M) does it conform to the http specification ?
	for (String::const_iterator it = strValue.begin();
			it != strValue.end(); it++) {
		char c;
		switch (c = *it) {

		case ' ':
			break;

		case ';':
			pAttributes->setValue(CCookiePrefix+strAttrName,strAttrValue);
			strAttrName.clear();
			strAttrValue.clear();
			bName=true;
			break;

		case '=':
			bName = false;
			break;

		default:
			if (bName)
				strAttrName += c;
			else
				strAttrValue += c;
		}
	}

	if(!bName)
		pAttributes->setValue(CCookiePrefix+strAttrName,strAttrValue);
}
/*************************************************************************/

}
}
}
