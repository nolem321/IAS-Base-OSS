/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/SessionTransacted.cpp
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
#include "SessionTransacted.h"

#include <commonlib/commonlib.h>

#include "exception/ODBCException.h"

#include "Connection.h"
#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection,SQL_AUTOCOMMIT_OFF){
	IAS_TRACER;
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo()," *** COMMIT ***");

/* 	SQLRETURN rc = SQLTransact(getConnection()->getSystem()->getEnvHandle(),
			                   this->hdbc,
			                   SQL_COMMIT);

//	ODBCException::ThrowOnError("commit",rc,SQL_HANDLE_DBC, (SQLHANDLE)hdbc);
 */
}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo()," *** ROLLBACK ***");

/* 	SQLRETURN rc = SQLTransact(getConnection()->getSystem()->getEnvHandle(),
			                   this->hdbc,
			                   SQL_ROLLBACK);

//	ODBCException::ThrowOnError("rollback",rc,SQL_HANDLE_DBC, (SQLHANDLE)hdbc);
 */
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
}
}
}
}
