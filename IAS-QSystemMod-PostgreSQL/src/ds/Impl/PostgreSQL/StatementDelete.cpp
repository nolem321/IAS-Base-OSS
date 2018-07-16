/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementDelete.cpp
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
#include "StatementDelete.h"
#include "exception/PostgreSQLException.h"
#include "log/LogLevel.h"

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
StatementDelete::StatementDelete(Session* pSession):
		PostgreSQL::Statement(pSession),
		Input(*(PostgreSQL::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementDelete::~StatementDelete() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementDelete::execute(){
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

 PostgreSQLException::ThrowOnError(strSQLText, pSession->getConnectionHandle(), rh);
}
/*************************************************************************/
}
}
}
}
