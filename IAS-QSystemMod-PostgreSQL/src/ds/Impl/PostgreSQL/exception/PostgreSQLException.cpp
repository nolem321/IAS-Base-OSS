/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/exception/PostgreSQLException.cpp
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
#include "PostgreSQLException.h"

#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace PostgreSQL{

/*************************************************************************/
PostgreSQLException::PostgreSQLException(){
	IAS_TRACER;
}
/*************************************************************************/
PostgreSQLException::PostgreSQLException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
PostgreSQLException::PostgreSQLException(const String& strInfo, PGconn  *conn){
	IAS_TRACER;
	this->setInfo(strInfo + ", Error: " + PQerrorMessage(conn));
}
/*************************************************************************/
PostgreSQLException::~PostgreSQLException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* PostgreSQLException::getName(){
	IAS_TRACER;
	return "PostgreSQLException";
}
/*************************************************************************/
class ConstraintViolationException :
		public virtual PostgreSQLException,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		PostgreSQLException(strInfo){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
void PostgreSQLException::ThrowOnError(const String& strInfo, PGconn  *conn){
	IAS_TRACER;

	if(PQstatus(conn) != CONNECTION_BAD)
		return;

	IAS_THROW(PostgreSQLException(strInfo, conn));
}
/*************************************************************************/
void PostgreSQLException::ThrowOnError(const String& strInfo, PGconn  *conn, PGresult *res){
	IAS_TRACER;

	if(PQresultStatus(res) == PGRES_COMMAND_OK)
		return;

	IAS_THROW(PostgreSQLException(strInfo + ", res="+TypeTools::IntToString(PQresultStatus(res)), conn));
}
/*************************************************************************/
}
}
}
} /* namespace IAS */
