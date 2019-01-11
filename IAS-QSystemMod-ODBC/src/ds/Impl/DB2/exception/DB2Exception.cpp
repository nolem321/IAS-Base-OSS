/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/exception/DB2Exception.cpp 
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License. 
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 * 
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 * 
 */
#include "DB2Exception.h"
#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>

#include <sqlcodes.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace DB2{

/*************************************************************************/
DB2Exception::DB2Exception(){
	IAS_TRACER;		
}
/*************************************************************************/
DB2Exception::DB2Exception(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
DB2Exception::DB2Exception(const String& strInfo, int rc){
	IAS_TRACER;
	//this->setInfo(strInfo+", Error: ("+TypeTools::IntToString(rc)+") "+GetErrorString(rc));
}
/*************************************************************************/
DB2Exception::~DB2Exception() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* DB2Exception::getName(){
	IAS_TRACER;
	return "DB2Exception";
}

/*************************************************************************/
static void _getDiagnostics(SQLSMALLINT htype, SQLHANDLE hndl, std::ostream& os, SQLINTEGER& sqlcode){

  SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
  SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
  SQLSMALLINT length, i;

  for(i=1; SQLGetDiagRec(htype, hndl, i, sqlstate, &sqlcode, message, SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS; i++){
    os<<"  SQLSTATE = "<<sqlstate<<", code = "<<sqlcode<<", "<<message;
  }

}
/*************************************************************************/
class ConstraintViolationException :
		public virtual DB2Exception,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		DB2Exception(strInfo){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
/*************************************************************************/
void DB2Exception::ThrowOnError(const String& strInfo, int rc, SQLSMALLINT htype, SQLHANDLE hndl){
	IAS_TRACER;

	switch(rc){

		case SQL_SUCCESS:
			return;

		case SQL_SUCCESS_WITH_INFO:
			//IAS_THROW(DB2Exception("SQL_SUCCESS_WITH_INFO"));
			return;

		case SQL_STILL_EXECUTING:
			IAS_THROW(DB2Exception("SQL_STILL_EXECUTING"));
			return;

		case SQL_NO_DATA_FOUND:
			IAS_THROW(DB2Exception("SQL_NO_DATA_FOUND"));
			return;

		case SQL_NEED_DATA:
			IAS_THROW(DB2Exception("SQL_NEED_DATA"));
			return;

		case SQL_ERROR:
			{
				StringStream ssTmp;
				SQLINTEGER   sqlcode;
				_getDiagnostics(htype,hndl,ssTmp,sqlcode);

				if(sqlcode == SQL_RC_E803 || sqlcode == SQL_RC_W803){
					IAS_THROW(ConstraintViolationException(ssTmp.str()));
				}

				IAS_LOG(LogLevel::INSTANCE.isError(),"Execute:["<<strInfo<<"]:"<<ssTmp.str());
				IAS_THROW(DB2Exception(ssTmp.str()));
			}
			break;

		case SQL_INVALID_HANDLE:
			IAS_THROW(DB2Exception("SQL_INVALID_HANDLE"));
		return;
	}
	IAS_THROW(DB2Exception(strInfo,rc));
}
/*************************************************************************/
}
}
}
} /* namespace IAS */
