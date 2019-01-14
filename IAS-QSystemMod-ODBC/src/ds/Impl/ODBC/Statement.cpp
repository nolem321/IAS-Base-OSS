/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/Statement.cpp
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
#include "Statement.h"
#include "exception/ODBCException.h"

#include <sqlite3.h>

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
Statement::Statement(Session* pSession):pSession(pSession),
		Tools::HandleStatement(pSession->getDBCHandle()){
	IAS_TRACER;

}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Statement::setSQLText(const String& strSQLText){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL1:["<<strSQLText<<"]");

	this->strSQLText.clear();

	bool bQuote=false;

	const char* sSrc=strSQLText.c_str();
	while(*sSrc)
		switch(*sSrc){

			case'\'':
				bQuote=!bQuote;
				this->strSQLText+=*sSrc++;
			break;

			case ':':
				sSrc++;
				if(!bQuote && isalpha(*sSrc)){
					if(isalpha(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					this->strSQLText+=" ? ";
				}
			break;

			default:
				this->strSQLText+=*sSrc++;
		}

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL2:X["<<this->strSQLText<<"]X");
}
/*************************************************************************/
void Statement::prepare(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Prepare:["<<strSQLText<<"]");

  checkForErrors(strSQLText,
      SQLPrepare(pHandle,
			          (SQLCHAR*)strSQLText.c_str(),
			          SQL_NTS)
   );

}
/*************************************************************************/
void Statement::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute:["<<strSQLText<<"]");

  checkForErrors(strSQLText,
     SQLExecute(pHandle)
   );
}
/*************************************************************************/
}
}
}
}
