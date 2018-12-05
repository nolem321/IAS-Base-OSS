/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/ResultSetOutput.cpp
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
#include "exception/LMDBException.h"
#include "Session.h"

#include <qs/fmt/FmtFactory.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
ResultSetOutput::ResultSetOutput(Statement& statement):
		statement(statement),
		bHasData(false),
    cursor(0){
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

  IAS_CHECK_IF_NULL(cursor);

  int rc = mdb_cursor_get(cursor, &values[iKeyIdx], &values[iDataIdx], !bReadAll ? MDB_SET : MDB_NEXT );

  if(rc){
    mdb_cursor_close(cursor);
    cursor = 0;
  }

	IAS_LOG(LogLevel::INSTANCE.isData(),"mdb_cursor_get RC:"<<rc);

  if(rc && rc != MDB_NOTFOUND)
    LMDBException::ThrowOnError("mdb_cursor_get", rc);

  return bHasData = (rc == 0);
}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(!bHasData)
		IAS_THROW(LMDBException("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabOptional.size())
		IAS_THROW(LMDBException("Fetch index of range."));


  fetchValue(values[iIdx], tabSetters[iIdx], dm);

	/* if(value.mv_size == 0) {

		if(!tabOptional[iIdx])
			tabSetters[iIdx]->unset(dm);

		}else{
 */

}
/*************************************************************************/
void ResultSetOutput::fetchValue(MDB_val& value, DM::Tools::Setter* pSetter, DM::DataObjectPtr& dm){
    IAS_TRACER;

		IAS_LOG(LogLevel::INSTANCE.isData(),"Fetch len:"<<value.mv_size);
		IAS_LOG(LogLevel::INSTANCE.isData(),"Fetch data:"<<(char*)value.mv_data);

		if(pSetter->getTargetTypeEnum() == DM::Type::DataObjectType ||
		   pSetter->getTargetTypeEnum() == DM::Type::AnyType){

			DM::DataObjectPtr dmValue;
			QS::Fmt::Formatter *pFormatter=statement.getSession()->getFormatter();
			StringStream ssValue((const char*)value.mv_data);
			pFormatter->read(dmValue,ssValue);

			pSetter->setDataObject(dm,dmValue);

		}else{
			pSetter -> setString(dm,(const char*)value.mv_data);
		}

}
/*************************************************************************/
void ResultSetOutput::close(){
	IAS_TRACER;

  if(cursor)
    mdb_cursor_close(cursor);
}
/*************************************************************************/
}
}
}
}
