/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Connection.cpp
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
#include "System.h"
#include "BlockIOWrapperFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
Connection::Connection(const Net::System* pSystem, BlockIOWrapperFactory* pBlockIOWrapperFactory):
		Net::Connection(pSystem),
		pBlockIOWrapperFactory(pBlockIOWrapperFactory){

	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);

	strHost=pBlockIOWrapperFactory->getConnection()->getHost();
}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

	case API::Session::SM_Transacted:
		return IAS_DFT_FACTORY<Sync::SessionTransacted>::Create(this);

	case API::Session::SM_NonTransacted:
		return IAS_DFT_FACTORY<Sync::SessionAutoCommit>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the Net module."));
	}

}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const String& Connection::getHost()const{
	IAS_TRACER;
	return strHost;
}
/*************************************************************************/
BlockIOWrapperFactory* Connection::getBlockIOWrapperFactory()const{
	IAS_TRACER;
	return pBlockIOWrapperFactory;
}
/*************************************************************************/
}
}
}
}
