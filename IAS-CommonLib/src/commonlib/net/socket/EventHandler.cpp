/*
 * File: IAS-CommonLib/src/commonlib/net/socket/EventHandler.cpp
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
#include "EventHandler.h"


namespace IAS {
namespace Net {
namespace Socket {

/*************************************************************************/
EventHandler::EventHandler(ServiceHandleFactory* pServiceHandleFactory,
						   Server*               pServer):
	ptrServiceHandleFactory(pServiceHandleFactory),
	Net::EventHandler(pServer->getSocket()),
	pServer(pServer){
	IAS_TRACER;
	subscribe(ET_InputReady);
}

/*************************************************************************/
EventHandler::~EventHandler() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void EventHandler::onInputReady(){
	IAS_TRACER;

	ptrServiceHandleFactory->createService(pServer->accept());
}
/*************************************************************************/
void EventHandler::onTimeout(){
	IAS_TRACER;
}
/*************************************************************************/
void EventHandler::onError(){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isError(), "Error event: "<<pFileHandle->getFD());
}
/*************************************************************************/
}
}
}
