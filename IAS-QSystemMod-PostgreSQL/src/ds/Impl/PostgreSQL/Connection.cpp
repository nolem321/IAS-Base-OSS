/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Connection.cpp
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

#include <commonlib/commonlib.h>

#include "SessionAutoCommit.h"
#include "SessionTransacted.h"
#include "System.h"
#include "log/LogLevel.h"

#include <libpq-fe.h>



namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {


const String& Connection::CDFmtTime("%H:%M:%S%F%Z");
const String& Connection::CDFmtDateTime("%Y-%m-%d %H:%M:%S%F%Z");
const String& Connection::CDFmtDate("%Y-%m-%d");

/*************************************************************************/
Connection::Connection(PostgreSQL::System* pSystem,
		const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter):
  Impl::Connection(pSystem, dmParameter),
	pSystem(pSystem){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),dmParameter->getName());

  int lib_ver = PQlibVersion();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"PQlibVersion:"<<lib_ver);

}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<PostgreSQL::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<PostgreSQL::SessionAutoCommit>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the FCGI module."));
	}

}
/*************************************************************************/
PostgreSQL::System* Connection::getSystem(){
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
