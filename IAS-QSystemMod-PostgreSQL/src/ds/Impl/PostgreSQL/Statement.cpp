/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Statement.cpp
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
#include "Statement.h"
#include "exception/PostgreSQLException.h"
#include "log/LogLevel.h"
#include <sqlite3.h>

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
Statement::Statement(Session* pSession):
		pSession(pSession),
		strPQName("IAS_"+TypeTools::IntToString((long)this)),
    bRemovePrepared(false){

	IAS_TRACER;
}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;

  if(bRemovePrepared){
      String strSQL("DEALLOCATE \"" + strPQName +"\";");

      PGResultHolder rh(PQexec(pSession->getConnectionHandle(), strSQL.c_str()));

    if (PQresultStatus(rh) != PGRES_TUPLES_OK)
		   IAS_LOG(true,"DEALLOCATE "<<PQresultStatus(rh)<<":"<<PQerrorMessage(pSession->getConnectionHandle()));
  }
}
/*************************************************************************/
Statement::PGResultHolder::PGResultHolder(PGresult *res):res(res){}
/*************************************************************************/
Statement::PGResultHolder::~PGResultHolder(){

	if(res)
		PQclear(res);
}
/*************************************************************************/
Statement::PGResultHolder& Statement::PGResultHolder::operator = (PGresult * res){

	if(this->res)
		PQclear(this->res);

	this->res = res;

	return *this;
};
/*************************************************************************/
Statement::PGResultHolder::operator PGresult *() {
	return res;
};
/*************************************************************************/
void Statement::setSQLText(const String& strSQLText){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"setSQL:["<<strSQLText<<"]");

	bool bQuote=false;

	const char* sSrc=strSQLText.c_str();

	int iCounter = 1;

	StringStream ssSQLText;
	while(*sSrc)
		switch(*sSrc){

			case'\'':
				bQuote=!bQuote;
				ssSQLText << *sSrc++;
			break;

			case ':':
				sSrc++;
				if(!bQuote){
					if(isalpha(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					if(isdigit(*sSrc))sSrc++;
					ssSQLText << "$"<<iCounter++;
				}
			break;

			default:
				ssSQLText<<*sSrc++;
		}

	this->strSQLText = ssSQLText.str();

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo() || true,"setSQL2:[" << this->strSQLText << "]");

}
/*************************************************************************/
void Statement::prepare(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isData(),"Prepare:["<<strSQLText<<"]");


	PGResultHolder rh(PQprepare(pSession->getConnectionHandle(),
						strPQName.c_str(),
	                    strSQLText.c_str(),
						0,
						NULL));

  if (PQresultStatus(rh) != PGRES_TUPLES_OK)
		 PostgreSQLException::ThrowOnError("PREPARE:" + strSQLText, pSession->getConnectionHandle(), rh);

  bRemovePrepared = true;
}
/*************************************************************************/
}
}
}
}
