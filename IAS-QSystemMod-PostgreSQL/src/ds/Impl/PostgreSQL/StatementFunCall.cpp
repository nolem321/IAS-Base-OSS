/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementFunCall.cpp
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
#include "StatementFunCall.h"
#include "exception/PostgreSQLException.h"
#include "log/LogLevel.h"

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
StatementFunCall::StatementFunCall(Session* pSession):
		PostgreSQL::Statement(pSession),
    Output(*(PostgreSQL::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementFunCall::~StatementFunCall() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementFunCall::setSQLText(const String& strSQLText){
  IAS_TRACER;
  Statement::setSQLText("SELECT " + strSQLText);
}
/*************************************************************************/
void StatementFunCall::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isData(),"Execute:["<<strSQLText<<"]");
	pSession->beginTxnIfNeed();

	rh = PQexecParams(pSession->getConnectionHandle(),
	                   strSQLText.c_str(),
	                   iNumValues,       /* one param */
	                   NULL,    /* let the backend deduce param type */
	                   tabValues,
	                   NULL,    /* don't need param lengths since text */
	                   NULL,    /* default to all text params */
	                   0);


  if (PQresultStatus(rh) != PGRES_TUPLES_OK)
		 PostgreSQLException::ThrowOnError(strSQLText, pSession->getConnectionHandle(), rh);

   iCurrentRow = 0;

	 int nFields = PQnfields(rh);
	 iNumRows = PQntuples(rh);

	 IAS_LOG(LogLevel::INSTANCE.isData()||true,"rows:"<<iNumRows<<" fields: "<<nFields);

}
/*************************************************************************/
}
}
}
}
