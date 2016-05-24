/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/Session.cpp
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
#include "Session.h"

#include <commonlib/commonlib.h>
#include "log/LogLevel.h"
#include "Connection.h"
#include "System.h"
#include "StatementInsert.h"
#include "StatementSelect.h"
#include "StatementDelete.h"
#include "StatementUpdate.h"

#include "exception/SQLiteException.h"

#include <qs/fmt/FmtFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
Session::Session(Connection* pConnection):
	pConnection(pConnection),
	db(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	String strConnection(EnvTools::Substitute(pConnection->getParameter()->getConnection()->getLocation()));

	String strFormatter("JSON");

	if(pConnection->getParameter()->isSetObjectFormatter())
		strFormatter=pConnection->getParameter()->getObjectFormatter();

	int rc = sqlite3_open(strConnection.c_str(),&db);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"opening:["<<strConnection<<"], rc="<<rc);
	SQLiteException::ThrowOnError(pConnection->getName(),rc);

	rc = sqlite3_busy_timeout(db,30000);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"setting timeout");

	SQLiteException::ThrowOnError(pConnection->getName(),rc);


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Fmt:["<<strFormatter<<"]");

	pFormatter=pConnection->getSystem()->getFmtFactory()->getFormatter(strFormatter);

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
	sqlite3_close(db);
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::StatementInsert*  Session::createInsert(){
	return IAS_DFT_FACTORY<StatementInsert>::Create(this);
}
/*************************************************************************/
API::StatementCall*  Session::createCall(){
	IAS_THROW(SQLiteException("Stored procedures are not available in SQLite."));
}
/*************************************************************************/
API::StatementSelect*  Session::createSelect(){
	return IAS_DFT_FACTORY<SQLite::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<SQLite::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<SQLite::StatementUpdate>::Create(this);
}
/*************************************************************************/
void Session::beginTxnIfNeed(){
	IAS_TRACER;
}
/*************************************************************************/

}
}
}
}

