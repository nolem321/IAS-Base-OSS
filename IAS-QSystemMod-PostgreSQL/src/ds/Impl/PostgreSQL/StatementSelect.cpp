/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementSelect.cpp
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
#include "StatementSelect.h"
#include "exception/PostgreSQLException.h"
#include "log/LogLevel.h"
#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
StatementSelect::StatementSelect(Session* pSession):
		PostgreSQL::Statement(pSession),
		Input(*(PostgreSQL::Statement*)this),
		ResultSetOutput(*(PostgreSQL::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementSelect::~StatementSelect() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementSelect::execute(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isData(),"Execute:["<<strSQLText<<"]");
	pSession->beginTxnIfNeed();

	rh = PQexecParams(pSession->getConnectionHandle(),
	                   strSQLText.c_str(),
	                   iNumValues,       /* one param */
	                   NULL,    /* let the backend deduce param type */
	                   tabValues,
	                   NULL,    /* don't need param lengths since text */
	                   NULL,    /* default to all text params */
	                   0);


	 if (PQresultStatus(rh) != PGRES_TUPLES_OK)
		 PostgreSQLException::ThrowOnError(strSQLText, pSession->getConnectionHandle(), rh);

	 iCurrentRow = 0;

	 int nFields = PQnfields(rh);
	 iNumRows = PQntuples(rh);
;
	 IAS_LOG(LogLevel::INSTANCE.isData()||true,"rows:"<<iNumRows<<" fields: "<<nFields);

}
/*************************************************************************/
}
}
}
}
