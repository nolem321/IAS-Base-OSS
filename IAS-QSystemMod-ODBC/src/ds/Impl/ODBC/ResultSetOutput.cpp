/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/ResultSetOutput.cpp
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
#include "ResultSetOutput.h"

#include "exception/ODBCException.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
ResultSetOutput::ResultSetOutput(Statement& statement):
		statement(statement),
		bHasData(false){
	IAS_TRACER;
}
/*************************************************************************/
ResultSetOutput::~ResultSetOutput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ResultSetOutput::addResultSetOutput(DM::Tools::Setter* pSetter, bool bOptional){

	IAS_TRACER;

	tabHolders.push_back(Holder::Base::Create(&statement,pSetter,bOptional));
	tabHolders.back()->define(tabHolders.size());
}
/*************************************************************************/
void ResultSetOutput::bindResultSetOutputs(){
	IAS_TRACER;
}
/*************************************************************************/
bool ResultSetOutput::next(){
	IAS_TRACER;

	SQLRETURN rc = SQLFetch((SQLHANDLE)statement);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"fetching: "<<tabHolders.size()<<" rc="<<rc);

	if(rc == SQL_NO_DATA_FOUND)
		return bHasData=false;

  statement.checkForErrors(statement.getSQLText()+" fetch", rc);

	return bHasData=true;
}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(!bHasData)
		IAS_THROW(ODBCException("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabHolders.size())
		IAS_THROW(ODBCException("Fetch index of range."));

	tabHolders[iIdx]->fetch(dm);

}
/*************************************************************************/
void ResultSetOutput::close(){
	IAS_TRACER;

  statement.checkForErrors(statement.getSQLText()+" fetch",
    SQLCloseCursor((SQLHANDLE)statement)
  );

}
/*************************************************************************/
}
}
}
}
