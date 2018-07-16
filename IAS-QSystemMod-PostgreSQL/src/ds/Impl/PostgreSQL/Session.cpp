/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Session.cpp
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

#include "exception/PostgreSQLException.h"

#include <qs/fmt/FmtFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
Session::Session(Connection* pConnection):
	pConnection(pConnection),
	conn(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	String strConnection(EnvTools::Substitute(pConnection->getParameter()->getConnection()->getLocation()));

	String strFormatter("JSON");

	if(pConnection->getParameter()->isSetObjectFormatter())
		strFormatter=pConnection->getParameter()->getObjectFormatter();

	StringStream ssParameters;
	ssParameters << "dbname='"<<pConnection->getParameter()->getConnection()->getLocation()<<"' ";

	if(pConnection->getParameter()->getConnection()->isSetHost())
		ssParameters << "host='"<<pConnection->getParameter()->getConnection()->getHost()<<"' ";

	if(pConnection->getParameter()->getConnection()->isSetPort())
		ssParameters << "port='"<<pConnection->getParameter()->getConnection()->getPort()<<"' ";

	if(pConnection->getParameter()->getConnection()->isSetUser())
		ssParameters << "user='"<<pConnection->getParameter()->getConnection()->getUser()<<"' ";

	if(pConnection->getParameter()->getConnection()->isSetPassword())
		ssParameters << "password='"<<pConnection->getParameter()->getConnection()->getPassword()<<"' ";

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"opening:["<<ssParameters.str()<<"]");

	conn = PQconnectdb(ssParameters.str().c_str());

	PostgreSQLException::ThrowOnError("Connect: "+ pConnection->getName(), conn);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Fmt:["<<strFormatter<<"]");

	pFormatter=pConnection->getSystem()->getFmtFactory()->getFormatter(strFormatter);

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;

	if(conn)
		PQfinish(conn);
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
	IAS_THROW(PostgreSQLException("Stored procedures are not available in PostgreSQL."));
}
/*************************************************************************/
API::StatementSelect*  Session::createSelect(){
	return IAS_DFT_FACTORY<PostgreSQL::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<PostgreSQL::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<PostgreSQL::StatementUpdate>::Create(this);
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

