/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Output.cpp
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
#include "Output.h"
#include "log/LogLevel.h"
#include "exception/PostgreSQLException.h"

#include "Session.h"

#include <qs/fmt/FmtFactory.h>
#include "ValueConverter.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
Output::Output(Statement& statement):
Input(statement),
statement(statement){
	IAS_TRACER;
}
/*************************************************************************/
Output::~Output() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Output::addInputOutput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;
  tabSetters.push_back(pSetter);
  lstElements.push_back(Element(strTag,pSetter));
}
/*************************************************************************/
void Output::fetch(DM::DataObjectPtr& dm){
	IAS_TRACER;

	if(iCurrentRow > iNumRows)
		IAS_THROW(PostgreSQLException("Fetch when no data found."));

  int iIdx = 0;

  for(SettersTable::const_iterator it = tabSetters.begin();
      it != tabSetters.end(); it++){

    const char* sValue;

    if((sValue = PQgetvalue(statement.getPGResult(), iCurrentRow, iIdx)) == NULL) {
			(*it)->unset(dm);
		}else{
      ValueConverter::ConvertFromPostgreSQL(statement, (*it), dm, sValue);
    }

    iIdx++;
	}

  iCurrentRow++;
}
/*************************************************************************/
void Output::addOutput(const String& strTag, DM::Tools::Setter *pSetter){
	IAS_TRACER;
  tabSetters.push_back(pSetter);
}
/*************************************************************************/
void Output::bindOutputs(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
