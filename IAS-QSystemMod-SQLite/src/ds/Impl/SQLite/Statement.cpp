/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/Statement.cpp
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
#include "exception/SQLiteException.h"
#include "log/LogLevel.h"
#include <sqlite3.h>

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
Statement::Statement(Session* pSession):pSession(pSession),stmt(0){
	IAS_TRACER;
}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;

	if(stmt)
		sqlite3_finalize(stmt);
}
/*************************************************************************/
void Statement::setSQLText(const String& strSQLText){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"setSQL:["<<strSQLText<<"]");
	this->strSQLText=strSQLText;



	//TODO more elegant FOR UPDATE hack for sqllite
	static const String CstrForUpdate(" FOR UPDATE ");

	if(String(CstrForUpdate).compare(this->strSQLText.c_str()+
			(this->strSQLText.length()-CstrForUpdate.length()))==0){
		this->strSQLText=this->strSQLText.substr(0,this->strSQLText.length()-CstrForUpdate.length());
	}
}
/*************************************************************************/
void Statement::prepare(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isData(),"Prepare:["<<strSQLText<<"]");

	int rc = sqlite3_prepare_v2(pSession->getDBHandle(),
			                    strSQLText.c_str(), -1,
			                    &stmt, NULL);

	SQLiteException::ThrowOnError(strSQLText,rc);
}
/*************************************************************************/
}
}
}
}
