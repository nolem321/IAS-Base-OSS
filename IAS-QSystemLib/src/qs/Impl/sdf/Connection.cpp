/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Connection.cpp
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

#include "SessionAutoCommit.h"
#include "SessionTransacted.h"
#include "Content.h"
#include "Message.h"
#include "ContentManager.h"
#include "System.h"

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
Connection::Connection(SDF::System* pSystem, const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
	strName(dmConnection->getHost()),
	pSystem(pSystem){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),strName);

	if(strName.compare("localhost") != 0 && !strName.empty())
		IAS_THROW(InternalException("Only localhost is supported."));

}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<QS::SDF::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<QS::SDF::SessionAutoCommit>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the file transport module."));
	}

}
/*************************************************************************/
API::Message* Connection::createMessage(){
	IAS_TRACER;
	return IAS_DFT_FACTORY< QS::SDF::Message >::Create();
}
/*************************************************************************/
API::ContentManager* Connection::getContentManager(){
	IAS_TRACER;
	return pSystem->getContentManager();
}
/*************************************************************************/
SDF::System* Connection::getSystem(){
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
