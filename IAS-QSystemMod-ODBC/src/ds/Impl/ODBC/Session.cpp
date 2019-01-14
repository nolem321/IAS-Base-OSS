/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/Session.cpp
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
#include "Session.h"

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "System.h"

#include "StatementInsert.h"
#include "StatementSelect.h"
#include "StatementDelete.h"
#include "StatementUpdate.h"
#include "StatementCall.h"
#include "StatementFunCall.h"

#include "exception/ODBCException.h"

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
Session::Session(Connection* pConnection, SQLSMALLINT iAutoCommit):
  DS::Impl::Session(pConnection),
	pConnection(pConnection),
	handleDBC(pConnection->getSystem()->getEnvHandle()){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	int rc=SQL_SUCCESS;

	const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter=pConnection->getParameter();

	String strLogin(dmParameter->getConnection()->isSetUser() ? dmParameter->getConnection()->getUser() : "");
	String strPassword(dmParameter->getConnection()->isSetPassword() ? dmParameter->getConnection()->getPassword() : "");
	String strDatabase(dmParameter->getConnection()->isSetLocation() ? dmParameter->getConnection()->getLocation() : "");

	if(dmParameter->isSetXaResource()){
		strDatabase=dmParameter->getXaResource();
	}

  handleDBC.checkForErrors("Connect[" + pConnection->getName() + "]",
	  SQLConnect(handleDBC,
					(SQLCHAR *)strDatabase.c_str(),	SQL_NTS,
					(SQLCHAR *)strLogin.c_str(), SQL_NTS,
					(SQLCHAR *)strPassword.c_str(), SQL_NTS)
  );

	IAS_LOG(LogLevel::INSTANCE.isError(),"opening:["<<pConnection->getName()<<"], rc="<<rc<<", hdbc="<<handleDBC);

  SQLCHAR dbms_name[256], dbms_ver[256];

  SQLGetInfo(handleDBC, SQL_DBMS_NAME, (SQLPOINTER)dbms_name, sizeof(dbms_name), NULL);
  SQLGetInfo(handleDBC, SQL_DBMS_VER, (SQLPOINTER)dbms_ver, sizeof(dbms_ver), NULL);

   IAS_LOG(LogLevel::INSTANCE.isInfo(),"DBMS Name: "<<dbms_name);
   IAS_LOG(LogLevel::INSTANCE.isInfo(),"DBMS Version: "<<dbms_ver);


	//Funny specs say that this is a POINTER  to the value (32bit integer).
  //	rc = SQLSetConnectAttr(this->hdbc,SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)(long)iAutoCommit,0);
	//ODBCException::ThrowOnError("SQLSetConnectAttr",0,0,0);

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
//	if(handleDBC.get() != 0)
//		SQLDisconnect(handleDBC.get());
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::StatementInsert*  Session::createInsert(){
	return IAS_DFT_FACTORY<StatementInsert>::Create(this);
}
/*************************************************************************/
API::StatementCall*  Session::createCall(){
	return IAS_DFT_FACTORY<StatementCall>::Create(this);
}
/*************************************************************************/
API::StatementFunCall*  Session::createFunCall(){
	return IAS_DFT_FACTORY<StatementFunCall>::Create(this);
}
/*************************************************************************/
API::StatementSelect*  Session::createSelect(){
	return IAS_DFT_FACTORY<ODBC::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<ODBC::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<ODBC::StatementUpdate>::Create(this);
}
/*************************************************************************/
}
}
}
}

