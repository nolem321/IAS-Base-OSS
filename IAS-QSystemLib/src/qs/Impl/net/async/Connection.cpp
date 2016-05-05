/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Connection.cpp
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
#include "System.h"
#include "Session.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {

/*************************************************************************/
Connection::Connection(const System* pSystem, Engine* pEngine):
	Net::Connection(pSystem),
	pEngine(pEngine){
	IAS_TRACER;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.bIsInfo,"iMode="<<iMode);

	switch(iMode){

	case API::Session::SM_Transacted:
		return IAS_DFT_FACTORY<Session>::Create(this);

	case API::Session::SM_NonTransacted:
		return IAS_DFT_FACTORY<Session>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the Net module."));
	}

}
/*************************************************************************/
}
}
}
}
