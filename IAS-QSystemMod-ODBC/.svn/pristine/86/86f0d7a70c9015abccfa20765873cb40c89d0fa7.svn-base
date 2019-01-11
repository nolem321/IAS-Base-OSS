/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/Connection.cpp
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
#include "Connection.h"

#include <commonlib/commonlib.h>

#include "SessionAutoCommit.h"
#include "SessionTransacted.h"
#include "SessionXAManaged.h"
#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
Connection::Connection(DB2::System* pSystem,
		   const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter):
  DS::Impl::Connection(pSystem, dmParameter),
	pSystem(pSystem){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSystem);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),dmParameter->getName());

}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	if(dmParameter->isSetXaResource() && iMode != API::Session::SM_XAManaged)
			IAS_THROW(BadUsageException("Only XA sessions are allowed when the XA resource name was defined."));

	if(!dmParameter->isSetXaResource() && iMode == API::Session::SM_XAManaged)
			IAS_THROW(BadUsageException("Only XA session requested but the connection was not defined as XA resource."));

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<DB2::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<DB2::SessionAutoCommit>::Create(this);

		case API::Session::SM_XAManaged:
			return IAS_DFT_FACTORY<DB2::SessionXAManaged>::Create(this);

		default:
			IAS_THROW(BadUsageException("Unsupported session mode requested for the FCGI module."));
		}

}
/*************************************************************************/
DB2::System* Connection::getSystem(){
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
