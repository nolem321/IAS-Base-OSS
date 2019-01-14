/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/System.cpp
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
#include "exception/ODBCException.h"


namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
System::System(){
	IAS_TRACER;

	handleEnv.checkForErrors("SQL_ATTR_ODBC_VERSION",
    SQLSetEnvAttr(handleEnv, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0)
  );

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** ODBC instance created.");
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;
	 	 return IAS_DFT_FACTORY<ODBC::Connection>::Create< ODBC::System* >(this,dmParameter);
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"** ODBC instance destroyed.");
}
/*************************************************************************/
}
}
}
}
/*************************************************************************/
extern "C"{
::IAS::DS::Impl::System* _ias_ds_system_odbc(){
	return IAS_DFT_FACTORY< ::IAS::DS::Impl::ODBC::System >::Create();
  }

}
