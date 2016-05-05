/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/StatementUpdate.cpp
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
#include "StatementUpdate.h"
#include "exception/SQLiteException.h"
#include "log/LogLevel.h"

#include "Session.h"


namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
StatementUpdate::StatementUpdate(Session* pSession):
		SQLite::Statement(pSession),
		Input(*(SQLite::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementUpdate::~StatementUpdate() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementUpdate::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isData(),"Execute:["<<strSQLText<<"]");
	pSession->beginTxnIfNeed();

	int rc=sqlite3_step(stmt);
	sqlite3_reset(stmt);
	SQLiteException::ThrowOnError(strSQLText,rc);

}
/*************************************************************************/
}
}
}
}
