/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/StatementInsert.cpp
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
#include "StatementInsert.h"
#include "exception/LMDBException.h"
#include "log/LogLevel.h"
#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
StatementInsert::StatementInsert(Session* pSession):
		LMDB::Statement(pSession),
		Input(*(LMDB::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementInsert::~StatementInsert() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementInsert::setSQLText(const String& strSQLText){
	IAS_TRACER;

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL:["<<strSQLText<<"]");


  if(strSQLText.compare("INSERT INTO table (key, value) VALUES (:I000, :I001)") == 0){
  } else {
    IAS_THROW(LMDBException("This SQL is not supported in LMDB: " + strSQLText));
  }

  Statement::setSQLText(strSQLText);
}
/*************************************************************************
void StatementInsert::prepare(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementInsert::execute(){
	IAS_TRACER;

  int rc = mdb_put(pSession->getTxn(),
                   pSession->getDBi(),
                   &elementKey.mv,
                   &elementValue.mv, 0);

  LMDBException::ThrowOnError("mdb_put", rc);
}
/*************************************************************************/
}
}
}
}
