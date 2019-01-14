/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/exception/ODBCException.cpp
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
#include "ODBCException.h"
#include <ds/api/exception/ConstraintViolationException.h>

#include <commonlib/commonlib.h>

namespace IAS{
namespace DS{
namespace Impl{
namespace ODBC{

/*************************************************************************/
ODBCException::ODBCException(){
	IAS_TRACER;
}
/*************************************************************************/
ODBCException::ODBCException(const String& strInfo){
	IAS_TRACER;
	this->setInfo(strInfo);
}
/*************************************************************************/
ODBCException::ODBCException(const String& strInfo, int rc){
	IAS_TRACER;
	//this->setInfo(strInfo+", Error: ("+TypeTools::IntToString(rc)+") "+GetErrorString(rc));
}
/*************************************************************************/
ODBCException::~ODBCException() throw(){
	IAS_TRACER;

}
/*************************************************************************/
const char* ODBCException::getName(){
	IAS_TRACER;
	return "ODBCException";
}

/*************************************************************************/
static void _getDiagnostics(SQLSMALLINT htype, SQLHANDLE hndl, std::ostream& os, SQLINTEGER& sqlcode){

  SQLCHAR message[SQL_MAX_MESSAGE_LENGTH + 1];
  SQLCHAR sqlstate[SQL_SQLSTATE_SIZE + 1];
  SQLSMALLINT length, i;

  bzero(sqlstate,SQL_SQLSTATE_SIZE + 1);
  bzero(message,SQL_MAX_MESSAGE_LENGTH + 1);

  for(i=1; SQLGetDiagRec(htype, hndl, i, sqlstate, &sqlcode, message, SQL_MAX_MESSAGE_LENGTH + 1, &length) == SQL_SUCCESS; i++){
    os<<std::endl<<i<<":  SQLSTATE = "<<sqlstate<<", code = "<<sqlcode<<", "<<message;
  }

}
/*************************************************************************/
class ConstraintViolationException :
		public virtual ODBCException,
		public virtual ::IAS::DS::API::ConstraintViolationException{
public:
	ConstraintViolationException(const String& strInfo):
		ODBCException(strInfo){};

	/*************************************************************************/
	const char* getName(){
		IAS_TRACER;
		return "ConstraintViolationException";
	}
};
/*************************************************************************/
/*************************************************************************/
void ODBCException::ThrowOnError(const String& strInfo,
                                 SQLRETURN rc,
                                 SQLHANDLE handle,
                                 SQLSMALLINT type){
	IAS_TRACER;

    SQLINTEGER   i = 0;
    SQLINTEGER   native;
    SQLCHAR      state[ 7 ];
    SQLCHAR      text[256];
    SQLSMALLINT  len;
    SQLRETURN    ret;

  if(SQL_SUCCEEDED(rc))
    return;

   StringStream ssInfo;
   ssInfo<<strInfo;

   SQLINTEGER sqlcode;

  _getDiagnostics(type, handle, ssInfo, sqlcode);
  IAS_LOG(true, rc<<" "+ssInfo.str());
	IAS_THROW(ODBCException(ssInfo.str(),rc));

/* 	switch(rc){

		case SQL_SUCCESS:
			return;

		case SQL_SUCCESS_WITH_INFO:
			//IAS_THROW(ODBCException("SQL_SUCCESS_WITH_INFO"));
			return;

		case SQL_STILL_EXECUTING:
			IAS_THROW(ODBCException("SQL_STILL_EXECUTING"));
			return;

		case SQL_NO_DATA_FOUND:
			IAS_THROW(ODBCException("SQL_NO_DATA_FOUND"));
			return;

		case SQL_NEED_DATA:
			IAS_THROW(ODBCException("SQL_NEED_DATA"));
			return;

		case SQL_ERROR:
			{
	/* 			StringStream ssTmp;
				SQLINTEGER   sqlcode;
				_getDiagnostics(htype,hndl,ssTmp,sqlcode);

				if(sqlcode == SQL_RC_E803 || sqlcode == SQL_RC_W803){
					IAS_THROW(ConstraintViolationException(ssTmp.str()));
				}

				IAS_LOG(LogLevel::INSTANCE.isError(),"Execute:["<<strInfo<<"]:"<<ssTmp.str());
				IAS_THROW(ODBCException(ssTmp.str()));
 */

}
/*************************************************************************/
}
}
}
} /* namespace IAS */
