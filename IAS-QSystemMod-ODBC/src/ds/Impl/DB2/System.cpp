/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/System.cpp 
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
#include "System.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "exception/DB2Exception.h"

#ifdef  IAS_DEMO_EXPIRATION
#include "demodist.h"
#endif

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
System::System(){
	IAS_TRACER;

#ifdef  IAS_DEMO_EXPIRATION
IAS::DemoNotice(IAS_DEMO_EXPIRATION," (DS) for IBM DB2 Databases");
#endif

	int rc=SQL_SUCCESS;

	rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
	DB2Exception::ThrowOnError("SQL_HANDLE_ENV",rc,SQL_HANDLE_ENV,henv);

	rc = SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,  (void *)SQL_OV_ODBC3, 0);
	DB2Exception::ThrowOnError("SQL_ATTR_ODBC_VERSION",rc,SQL_HANDLE_ENV,henv);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** DB2 instance created.");
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;
	 	 return IAS_DFT_FACTORY<DB2::Connection>::Create< DB2::System* >(this,dmParameter);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** DB2 instance destroyed.");
}
/*************************************************************************/
}
}
}
}
/*************************************************************************/
extern "C"{
::IAS::DS::Impl::System* _ias_ds_system_db2(){
	return IAS_DFT_FACTORY< ::IAS::DS::Impl::DB2::System >::Create();
  }

}
