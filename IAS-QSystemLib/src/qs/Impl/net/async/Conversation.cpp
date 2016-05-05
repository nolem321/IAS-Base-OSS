/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Conversation.cpp
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
#include "Conversation.h"

#include <qs/log/LogLevel.h>

#include <qs/Impl/net/Message.h>
#include <qs/Impl/net/System.h>

#include "Engine.h"
#include "System.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {


/*************************************************************************/
const Conversation::Key Conversation::C_AnyKey(0);

Conversation::Key _GenKey(){
	static Mutex mutex;
	static long  key=Conversation::C_AnyKey;
	Mutex::Locker locker(mutex);
	return ++key;
}
/*************************************************************************/
Conversation::Conversation(IAS::Net::FileHandle* pFileHandle,
						   Engine *pEngine,
						   bool bSuppressInitialization):
		IAS::Net::EventHandler(pFileHandle),
		ptrFileHandle(pFileHandle),
		pEngine(pEngine),
		pBlockIO(0),
		key(_GenKey()){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pEngine);

	if(!bSuppressInitialization)
		initialize(pFileHandle);
}
/*************************************************************************/
Conversation::~Conversation() throw(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Disconnected !");
}
/*************************************************************************/
void Conversation::initialize(IAS::Net::IBlockIO *pBlockIO){
	IAS_TRACER;
	this->pBlockIO=pBlockIO;
	ptrInputMessage=IAS_DFT_FACTORY< QS::Net::Message >::Create();
	ptrInputMsgPump = pEngine->getSystem()->getPumpFactory()->createInputPump(pBlockIO,ptrInputMessage);
	subscribe(IAS::Net::EventHandler::ET_InputReady);

	makeWritable();

}
/*************************************************************************/
void Conversation::onInputReady(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(ptrInputMsgPump){

		IAS::Net::IBlockIO::Result rc;

		try{
			rc=ptrInputMsgPump->pump();
		}catch(EndOfDataException& e){
			setDeletePending();
			return;
		}

		if(rc == IAS::Net::IBlockIO::RC_OK){
			unsubscribe(IAS::Net::EventHandler::ET_InputReady);
			ptrInputMsgPump=0;

			makeReadable();
		}
	}
}
/*************************************************************************/
void Conversation::onOutputReady(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(ptrOutputMsgPump){

		IAS::Net::IBlockIO::Result rc=ptrOutputMsgPump->pump();

		if(rc == IAS::Net::IBlockIO::RC_OK){

			unsubscribe(IAS::Net::EventHandler::ET_OutputReady);

			ptrOutputMsgPump=0;
			ptrOutputMessage=0;

			//TODO (M) setDeletePending() if auto close in http.
			//setDeletePending();
			makeWritable();
		}
	}
}
/*************************************************************************/
void Conversation::makeWritable(){
	IAS_TRACER;

	addUsage();
	pEngine->addWritable(this);

}
/*************************************************************************/
void Conversation::makeReadable(){
	IAS_TRACER;

	addUsage();
	pEngine->addReadable(this);

}
/*************************************************************************/
void Conversation::setDeletePending(){
	IAS_TRACER;

	int iCount=pEngine->remove(this);

	while(iCount--)
		removeUsage();

	IAS::Net::EventHandler::setDeletePending();
}
/*************************************************************************/
Message* Conversation::getMessage(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(! ptrInputMsgPump.isNull())
		IAS_THROW(ItemNotFoundException("Net::Async::Conversation::getMessage()"));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrResult(ptrInputMessage.pass());

	ptrInputMessage=IAS_DFT_FACTORY< QS::Net::Message >::Create();

	//TODO we enter unstable state if pump will not be created so this ugly code.
	try{
		ptrInputMsgPump = pEngine->getSystem()->getPumpFactory()->createInputPump(pBlockIO,ptrInputMessage);

	}catch(Exception& e){
		ptrInputMessage=ptrResult.pass();
		throw;
	}

	subscribe(IAS::Net::EventHandler::ET_InputReady);

	return ptrResult.pass();
}
/*************************************************************************/
void Conversation::putMessage(Message* pMessage){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(! ptrOutputMessage.isNull())
		IAS_THROW(BadUsageException("Only one message can be scheduled in asynchronous network at this moment."));

	ptrOutputMessage = IAS_DFT_FACTORY<Message>::Create(pMessage);
	ptrOutputMsgPump = pEngine->getSystem()->getPumpFactory()->createOutputPump(pBlockIO,ptrOutputMessage);

	subscribe(IAS::Net::EventHandler::ET_OutputReady);
}
/*************************************************************************/
Engine *Conversation::getEngine()const{
	IAS_TRACER;
	return pEngine;
}
/*************************************************************************/
void Conversation::resume(){
	IAS_TRACER;
	pEngine->resumeConversation(this);
}
/*************************************************************************/
}
}
}
}
