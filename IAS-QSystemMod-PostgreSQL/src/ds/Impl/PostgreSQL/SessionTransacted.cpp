/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/SessionTransacted.cpp
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
#include "SessionTransacted.h"

#include "exception/PostgreSQLException.h"

#include "log/LogLevel.h"
#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection),
	bTxnStarted(false){
	IAS_TRACER;

	beginTxnIfNeed();
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;

	if(!bTxnStarted)
		return;

	PGresult *pResult = PQexec(conn, "COMMIT");

	PostgreSQLException::ThrowOnError("COMMIT", conn, pResult);

	bTxnStarted=false;
}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

	if(!bTxnStarted)
		return;

	PGresult *pResult = PQexec(conn, "ROLLBACK");

	PostgreSQLException::ThrowOnError("ROLLBACK", conn, pResult);

	bTxnStarted=false;
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
void SessionTransacted::beginTxnIfNeed(){
	IAS_TRACER;

	if(bTxnStarted)
		return;

  IAS_LOG(LogLevel::INSTANCE.isData(),"Start transaction");

	PGresult *pResult = PQexec(conn, "BEGIN");

	PostgreSQLException::ThrowOnError("BEGIN", conn, pResult);

	bTxnStarted=true;
}
/*************************************************************************/
}
}
}
}
