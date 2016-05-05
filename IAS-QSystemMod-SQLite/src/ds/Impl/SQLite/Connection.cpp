/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/Connection.cpp
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

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
Connection::Connection(SQLite::System* pSystem,
		const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter):
	dmParameter(dmParameter->duplicateParameter()),
	pSystem(pSystem){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),dmParameter->getName());

}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<SQLite::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<SQLite::SessionAutoCommit>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the FCGI module."));
	}

}
/*************************************************************************/
SQLite::System* Connection::getSystem(){
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
