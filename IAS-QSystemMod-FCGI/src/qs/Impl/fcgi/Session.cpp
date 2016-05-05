/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/Session.cpp
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

namespace IAS {
namespace QS {
namespace FCGI {

Mutex Session::mutexAccept;
Mutex Session::mutexInit;
bool Session::bInitialized(false);

/*************************************************************************/
Session::Session(Connection* pConnection):
	pConnection(pConnection),
	bAccepted(false){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	Mutex::Locker locker(mutexInit);
	if(!bInitialized){
		FCGX_Init();
		bInitialized=true;
	}
	 FCGX_InitRequest(&request, 0, 0);
}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;

	if(bAccepted)
		finish();

}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::Controller*  Session::createController(const API::Destination& refDestination){
	IAS_TRACER;
	IAS_THROW(BadUsageException("There is no controller for FCGI"));
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
	IAS_THROW(BadUsageException("Requester not supported for FCGI"));
}
/*************************************************************************/
API::Responder* Session::createResponder(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Responder>::Create<Session*>(this);
}
/*************************************************************************/
void Session::accept(){
	IAS_TRACER;

	if(bAccepted)
		finish();

	//TODO (M) is it an error ? eg. auto commit sessions ?
	//IAS_THROW(InternalException("Second call of FCGX_Accept_r without FCGX_Finish_r."));

	Mutex::Locker locker(mutexAccept);

	Thread::Cancellation tc(true);

	int rc = FCGX_Accept_r(&request);
	if(rc < 0)
		IAS_THROW(SystemException("FCGX_Accept_r",-rc));
	bAccepted=true;
}
/*************************************************************************/
FCGX_Request* Session::getRequest(){
	IAS_TRACER;

	if(!bAccepted)
		IAS_THROW(InternalException("Prior call of accept() required."));


	return &request;
}
/*************************************************************************/
void Session::finish(){
	IAS_TRACER;
	FCGX_Finish_r(&request);
	bAccepted=false;
}
/*************************************************************************/

}
}
}
