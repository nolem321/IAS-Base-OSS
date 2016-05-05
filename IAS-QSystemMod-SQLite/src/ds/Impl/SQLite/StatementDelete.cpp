/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/StatementDelete.cpp
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
#include "StatementDelete.h"
#include "exception/SQLiteException.h"
#include "log/LogLevel.h"

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
StatementDelete::StatementDelete(Session* pSession):
		SQLite::Statement(pSession),
		Input(*(SQLite::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementDelete::~StatementDelete() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementDelete::execute(){
	IAS_TRACER;

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
