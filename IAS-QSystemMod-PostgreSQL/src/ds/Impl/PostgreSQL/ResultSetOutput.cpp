/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/ResultSetOutput.cpp
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
#include "exception/PostgreSQLException.h"
#include "Session.h"

#include <qs/fmt/FmtFactory.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
ResultSetOutput::ResultSetOutput(Statement& statement):
		statement(statement),
		iCurrentRow(0),
		iNumRows(0){
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

	if(iCurrentRow++ < iNumRows)
		return true;

	return false;

}
/*************************************************************************/
void ResultSetOutput::fetch(int iIdx, DM::DataObjectPtr& dm){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo()||true,"fetching: "<<tabOptional.size()<<" iCurrentIdx: "<<iCurrentRow<<", iNumRows: "<<iNumRows);

	if(iCurrentRow > iNumRows)
		IAS_THROW(PostgreSQLException("Fetch when no data found."));

	if(iIdx < 0 || iIdx >= tabOptional.size())
		IAS_THROW(PostgreSQLException("Fetch index of range."));

	const char* sValue;

	if((sValue = PQgetvalue(statement.getPGResult(), iCurrentRow - 1, iIdx)) == NULL) {

		if(!tabOptional[iIdx])
			tabSetters[iIdx]->unset(dm);

		}else{

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
}
/*************************************************************************/
}
}
}
}
