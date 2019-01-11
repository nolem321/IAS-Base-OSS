/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/SessionXAManaged.cpp 
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
#include "SessionXAManaged.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
SessionXAManaged::SessionXAManaged(Connection* pConnection):
		Session(pConnection,SQL_AUTOCOMMIT_OFF){
	IAS_TRACER;
}

/*************************************************************************/
SessionXAManaged::~SessionXAManaged() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionXAManaged::commit(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
void SessionXAManaged::rollback(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
Session::TransactionMode SessionXAManaged::getMode()const{
	return Session::SM_XAManaged;
}
/*************************************************************************/
}
}
}
}
