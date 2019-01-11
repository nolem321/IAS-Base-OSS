/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Session.cpp
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
#include "Responder.h"
#include "Requester.h"

#include "BlockIOWrapperFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
Session::Session(Connection *pConnection):
	pConnection(pConnection){

	IAS_TRACER;
}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IAS::Net::IBlockIO* Session::getBlockIO(){
	IAS_TRACER;
	return getBlockIOWrapper()->getBlockIO();
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
API::Requester*  Session::createRequester(const API::Destination& outDestination,
										  const API::Destination& inDestination){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Requester>::Create<Session*,
											   const API::Destination&,
											   const API::Destination&>(this, outDestination,inDestination);
}
/*************************************************************************/
API::Responder* Session::createResponder(){
	IAS_TRACER;
	return IAS_DFT_FACTORY<Responder>::Create<Session*>(this);
}
/*************************************************************************/
void Session::setTimeout(int iTimeout){
	IAS_TRACER;

	getBlockIOWrapper()->getFileHandle()->setTimeout(iTimeout);
}
/*************************************************************************/
Connection *Session::getConnection()const{
	return pConnection;
};
/*************************************************************************/
void Session::purgeIOWrapper(){
	IAS_TRACER;
	ptrBlockIOWrapper=0;
}
/*************************************************************************/
BlockIOWrapper* Session::getBlockIOWrapper(){
	IAS_TRACER;

	if(ptrBlockIOWrapper.isNull())
		ptrBlockIOWrapper=pConnection->getBlockIOWrapperFactory()->createBlockIOWrapper();

	return ptrBlockIOWrapper;
}
/*************************************************************************/
void Session::updateAttributes(API::Attributes* pAttributes)const{
	IAS_TRACER;

	if(ptrBlockIOWrapper)
		pAttributes->setValue("REMOTE_ADDR",ptrBlockIOWrapper->getPeer());

}
/*************************************************************************/

}
}
}
}
