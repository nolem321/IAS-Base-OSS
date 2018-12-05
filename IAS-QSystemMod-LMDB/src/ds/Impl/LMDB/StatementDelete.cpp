/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/StatementDelete.cpp
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
#include "exception/LMDBException.h"
#include "log/LogLevel.h"

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
StatementDelete::StatementDelete(Session* pSession):
		LMDB::Statement(pSession),
		Input(*(LMDB::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementDelete::~StatementDelete() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementDelete::setSQLText(const String& strSQLText){
	IAS_TRACER;

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL:["<<strSQLText<<"]");

  if(strSQLText.compare("DELETE  FROM table WHERE key  =  :I000") == 0){
  } else {
    IAS_THROW(LMDBException("This SQL is not supported in LMDB: " + strSQLText));
  }

  Statement::setSQLText(strSQLText);
}
/*************************************************************************/
void StatementDelete::execute(){
	IAS_TRACER;


  int rc = mdb_del(pSession->getTxn(),
                   pSession->getDBi(),
                   &elementKey.mv,
                   &elementValue.mv);

  LMDBException::ThrowOnError("mdb_del", rc);


}
/*************************************************************************/
}
}
}
}
