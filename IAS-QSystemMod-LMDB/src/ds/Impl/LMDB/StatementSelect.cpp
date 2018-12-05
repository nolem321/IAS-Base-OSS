/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/StatementSelect.cpp
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
#include "exception/LMDBException.h"
#include "log/LogLevel.h"
#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
StatementSelect::StatementSelect(Session* pSession):
		LMDB::Statement(pSession),
		Input(*(LMDB::Statement*)this),
		ResultSetOutput(*(LMDB::Statement*)this){
	IAS_TRACER;
}

/*************************************************************************/
StatementSelect::~StatementSelect() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void StatementSelect::setSQLText(const String& strSQLText){
	IAS_TRACER;

  IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL:["<<strSQLText<<"]");


  if(strSQLText.compare("SELECT data FROM table WHERE key  =  :I000") == 0){

    iKeyIdx = 1;
    iDataIdx = 0;

  } else if(strSQLText.compare("SELECT key, data FROM table") == 0){

    iKeyIdx = 0;
    iDataIdx = 1;

    bReadAll = true;

  } else {
    IAS_THROW(LMDBException("This SQL is not supported in LMDB: " + strSQLText));
  }

  Statement::setSQLText(strSQLText);
}
/*************************************************************************/
void StatementSelect::execute(){
	IAS_TRACER;


  int rc = mdb_cursor_open(pSession->getTxn(),
                           pSession->getDBi(), &cursor);

  LMDBException::ThrowOnError("mdb_cursor_open", rc);

  if(!Input::elementKey.strTag.empty())
    ResultSetOutput::values[iKeyIdx] = Input::elementKey.mv;
  else{
    ResultSetOutput::values[iKeyIdx].mv_size=0;
    ResultSetOutput::values[iKeyIdx].mv_data=0;
  }

  if(!Input::elementValue.strTag.empty())
    ResultSetOutput::values[iDataIdx] = Input::elementValue.mv;
  else{
    ResultSetOutput::values[iDataIdx].mv_size=0;
    ResultSetOutput::values[iDataIdx].mv_data=0;
  }

    bHasData = true;

}
/*************************************************************************/
}
}
}
}
