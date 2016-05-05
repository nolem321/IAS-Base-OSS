/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/exception/SQLiteException.cpp
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
#include "SQLiteException.h"

#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>
#include <sqlite3.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace SQLite{

/*************************************************************************/
SQLiteException::SQLiteException(){
	IAS_TRACER;		
}
/*************************************************************************/
SQLiteException::SQLiteException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
SQLiteException::SQLiteException(const String& strInfo, int rc){
	IAS_TRACER;
	this->setInfo(strInfo+", Error: ("+TypeTools::IntToString(rc)+") "+GetErrorString(rc));
}
/*************************************************************************/
SQLiteException::~SQLiteException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* SQLiteException::getName(){
	IAS_TRACER;
	return "SQLiteException";
}
/*************************************************************************/
/*************************************************************************/
class ConstraintViolationException :
		public virtual SQLiteException,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		SQLiteException(strInfo, SQLITE_CONSTRAINT){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
/*************************************************************************/
void SQLiteException::ThrowOnError(const String& strInfo, int rc){
	IAS_TRACER;

	if(rc == SQLITE_OK || rc == SQLITE_DONE)
		return;

	if(rc == SQLITE_CONSTRAINT)
		IAS_THROW(ConstraintViolationException(strInfo));

	IAS_THROW(SQLiteException(strInfo,rc));
}
/*************************************************************************/
const char* SQLiteException::GetErrorString(int rc){
	IAS_TRACER;
	switch(rc){

	case  SQLITE_OK           :  return "Successful result.";

	case  SQLITE_ERROR       :  return   "SQL error or missing database.";
	case  SQLITE_INTERNAL    :  return   "Internal logic error in SQLite.";
	case  SQLITE_PERM        :  return   "Access permission denied.";
	case  SQLITE_ABORT       :  return   "Callback routine requested an abort.";
	case  SQLITE_BUSY        :  return   "The database file is locked.";
	case  SQLITE_LOCKED      :  return   "A table in the database is locked.";
	case  SQLITE_NOMEM       :  return   "A malloc() failed.";
	case  SQLITE_READONLY    :  return   "Attempt to write a readonly database.";
	case  SQLITE_INTERRUPT   :  return   "Operation terminated by sqlite3_interrupt()";
	case  SQLITE_IOERR       :  return   "Some kind of disk I/O error occurred.";
	case  SQLITE_CORRUPT     :  return   "The database disk image is malformed.";
	case  SQLITE_NOTFOUND    :  return   "Unknown opcode in sqlite3_file_control().";
	case  SQLITE_FULL        :  return   "Insertion failed because database is full.";
	case  SQLITE_CANTOPEN    :  return   "Unable to open the database file.";
	case  SQLITE_PROTOCOL    :  return   "Database lock protocol error.";
	case  SQLITE_EMPTY       :  return   "Database is empty.";
	case  SQLITE_SCHEMA      :  return   "The database schema changed.";
	case  SQLITE_TOOBIG      :  return   "String or BLOB exceeds size limit.";
	case  SQLITE_CONSTRAINT  :  return   "Abort due to constraint violation.";
	case  SQLITE_MISMATCH    :  return   "Data type mismatch.";
	case  SQLITE_MISUSE      :  return   "Library used incorrectly.";
	case  SQLITE_NOLFS       :  return   "Uses OS features not supported on host.";
	case  SQLITE_AUTH        :  return   "Authorization denied.";
	case  SQLITE_FORMAT      :  return   "Auxiliary database format error.";
	case  SQLITE_RANGE       :  return   "2nd parameter to sqlite3_bind out of range.";
	case  SQLITE_NOTADB      :  return   "File opened that is not a database file.";
//	case  SQLITE_NOTICE      :  return   "Notifications from sqlite3_log().";
//	case  SQLITE_WARNING     :  return   "Warnings from sqlite3_log().";
	case  SQLITE_ROW         :  return   "sqlite3_step() has another row ready.";
	case  SQLITE_DONE        :  return   "sqlite3_step() has finished executing.";
	default:
	 return "No description for this error";
	}

}
/*************************************************************************/
}
}
}
} /* namespace IAS */
