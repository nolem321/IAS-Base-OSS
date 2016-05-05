/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Session.cpp
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
#include "Session.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Connection.h"

#include "Producer.h"
#include "Consumer.h"
#include "Subscriber.h"
#include "Publisher.h"
#include "Browser.h"
#include "Responder.h"
#include "Requester.h"
#include "Controller.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Session::Session(Shared::Session* pSession,Connection* pConnection):
	pConnection(pConnection),
	ptrSession(pSession){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);
}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::Controller*  Session::createController(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Controller>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Producer*  Session::createProducer(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Producer>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Consumer*  Session::createConsumer(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Consumer>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Browser*  Session::createBrowser(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Browser>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Subscriber*  Session::createSubscriber(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Subscriber>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Publisher*  Session::createPublisher(const API::Destination& refDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Publisher>::Create<Session*, const API::Destination&>(this, refDestination);
}
/*************************************************************************/
API::Requester*  Session::createRequester(const API::Destination& outDestination,
										  const API::Destination& inDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Requester>::Create<Session*, const API::Destination&,const API::Destination&>
			(this, outDestination,inDestination);
}
/*************************************************************************/
API::Responder* Session::createResponder(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Responder>::Create<Session*>(this);
}
/*************************************************************************/
}
}
}
