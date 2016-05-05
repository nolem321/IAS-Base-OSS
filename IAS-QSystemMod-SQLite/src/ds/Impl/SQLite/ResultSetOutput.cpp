/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/ResultSetOutput.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "ResultSetOutput.h"
#include "log/LogLevel.h"
#include "exception/SQLiteException.h"
#include "Session.h"

#include <qs/fmt/FmtFactory.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

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
	tabOptional.push_back(bOptional);
	tabSetters.push_back(pSetter);
}
/*************************************************************************/
void ResultSetOutput::bindResultSetOutputs(){
	IAS_TRACER;
}
/*************************************************************************/
bool ResultSetOutput::next(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"fetching: "<<tabOptional.size());

	int rc = sqlite3_step(statement.getSQLiteHandle());

	if(rc == SQLITE_DONE)
		return bHasData=false;

	if(rc != SQLITE_ROW)
		SQLiteException::ThrowOnError(statement.getSQLText()+" fetch.",rc);

	IAS_LOG(LogLevel::INSTANCE.isData(),"Got a row!");

	return bHasData=true;
}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(!bHasData)
		IAS_THROW(SQLiteException("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabOptional.size())
		IAS_THROW(SQLiteException("Fetch index of range."));

	if(sqlite3_column_type(statement.getSQLiteHandle(),iIdx) == SQLITE_NULL) {

		if(!tabOptional[iIdx])
			tabSetters[iIdx]->unset(dm);

		}else{

		const char *sValue=(const char*)sqlite3_column_text(statement.getSQLiteHandle(),iIdx);

		if(!sValue)
			IAS_THROW(SQLiteException(statement.getSQLText()+"fetch column"));

		IAS_LOG(LogLevel::INSTANCE.isData(),"Fetch:["<<iIdx<<"]="<<sValue);

		if(tabSetters[iIdx]->getTargetTypeEnum() == DM::Type::DataObjectType ||
		   tabSetters[iIdx]->getTargetTypeEnum() == DM::Type::AnyType){

			DM::DataObjectPtr dmValue;
			QS::Fmt::Formatter *pFormatter=statement.getSession()->getFormatter();
			StringStream ssValue(sValue);
			pFormatter->read(dmValue,ssValue);

			tabSetters[iIdx]->setDataObject(dm,dmValue);

		}else{
			tabSetters[iIdx]->setString(dm,sValue);
		}

	}

}
/*************************************************************************/
void ResultSetOutput::close(){
	IAS_TRACER;

	int rc = sqlite3_reset(statement.getSQLiteHandle());

	SQLiteException::ThrowOnError(statement.getSQLText(),rc);
}
/*************************************************************************/
}
}
}
}
