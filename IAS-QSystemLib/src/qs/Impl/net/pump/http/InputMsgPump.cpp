/*
 * File: IAS-QSystemLib/src/qs/Impl/net/pump/http/InputMsgPump.cpp
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
#include <unistd.h>
namespace IAS {
namespace QS {
namespace Net {
namespace Pump {
namespace HTTP {
/*************************************************************************/
class MessageIDGenerator{
public:
	MessageIDGenerator():iSequence(0){
		StringStream ssTmp;
		ssTmp<<"NET"<<getpid()%10000<<"T"<<((long)(Timestamp(true))%100000);
		strPrefix=ssTmp.str();
	}

	String getNextMID(){
		StringStream ssTmp;
		ssTmp<<strPrefix<<"S"<<iSequence;
		return ssTmp.str();
	}

	static MessageIDGenerator TheInstance;
protected:
	Mutex mutex;
	long  iSequence;
	String strPrefix;
};

MessageIDGenerator MessageIDGenerator::TheInstance;
/*************************************************************************/
InputMsgPump::InputMsgPump(::IAS::Net::IBlockIO* pBlockIO, Message* pMessage):
		pBlockIO(pBlockIO),
		pMessage(pMessage),
		iState(S_Attributes){
	IAS_TRACER;
}

/*************************************************************************/
InputMsgPump::~InputMsgPump() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::Net::IBlockIO::Result InputMsgPump::pump(){
	IAS_TRACER;

	if(!ptrInputPump)
		return ::IAS::Net::IBlockIO::RC_OK;

	::IAS::Net::IBlockIO::Result rc=ptrInputPump->pump();

	if(rc != ::IAS::Net::IBlockIO::RC_OK)
		return rc;

	if(iState == S_Content){
		ptrInputPump=0;
		return ::IAS::Net::IBlockIO::RC_OK;
	}

	pMessage->getBaseAttributes()->setMID(MessageIDGenerator::TheInstance.getNextMID());
	pMessage->getBaseAttributes()->setFormat("JSON");
	pMessage->getBaseAttributes()->setReplyTo("dummynet");

	onHeaderReady();

	iState = S_Content;

	if(getHeader()->getTransferEncoding().compare("chunked") == 0){

		ptrInputPump = IAS_DFT_FACTORY< ::IAS::Net::HTTP::ChunkedInputPump>::
				Create< ::IAS::Net::IBlockIO*, std::ostream&>(pBlockIO,*pMessage->getContent());

	}else{

		size_t     iDataLength;

		if(!getHeader()->isSetContentLength() || (iDataLength=getHeader()->getContentLength()) == 0)
			return ::IAS::Net::IBlockIO::RC_OK;

		ptrInputPump = IAS_DFT_FACTORY< ::IAS::Net::Async::KnownLengthInputPump>::
				Create< ::IAS::Net::IBlockIO*, std::ostream&>(pBlockIO,*pMessage->getContent(),iDataLength);
	}

	rc=ptrInputPump->pump();

	if(rc == ::IAS::Net::IBlockIO::RC_OK)
		ptrInputPump=0;

	return rc;
}
/*************************************************************************/
}
}
}
}
}
