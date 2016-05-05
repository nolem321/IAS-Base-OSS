/*
 * File: IAS-QSystemLib/src/qs/Impl/net/Connection.cpp
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
#include "Connection.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Content.h"
#include "Message.h"
#include "System.h"

namespace IAS {
namespace QS {
namespace Net {

/*************************************************************************/
Connection::Connection(const Net::System* pSystem):
		pSystem(pSystem){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);
}
/*************************************************************************/
API::Message* Connection::createMessage(){
	IAS_TRACER;
	return IAS_DFT_FACTORY< QS::Net::Message >::Create();
}
/*************************************************************************/
API::ContentManager* Connection::getContentManager(){
	IAS_TRACER;
	return pSystem->getContentManager();
}
/*************************************************************************/
const Net::System* Connection::getSystem(){
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Administrator*   Connection::createAdministrator(){
	IAS_TRACER;
	IAS_THROW(BadUsageException("Administration object not allowed for this protocol."));
}
/*************************************************************************/
}
}
}
