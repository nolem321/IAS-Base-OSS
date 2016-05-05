/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/SessionTransacted.cpp
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

#include "exception/SQLiteException.h"

#include "log/LogLevel.h"
#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

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

	int rc = sqlite3_exec(db, "COMMIT", 0, 0, 0);
	SQLiteException::ThrowOnError("COMMIT",rc);

	bTxnStarted=false;
}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

	if(!bTxnStarted)
		return;

	int rc = sqlite3_exec(db, "ROLLBACK", 0, 0, 0);
	SQLiteException::ThrowOnError("ROLLBACK",rc);

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

	int rc = sqlite3_exec(db, "BEGIN IMMEDIATE", 0, 0, 0);
	SQLiteException::ThrowOnError("BEGIN",rc);

	bTxnStarted=true;
}
/*************************************************************************/
}
}
}
}
