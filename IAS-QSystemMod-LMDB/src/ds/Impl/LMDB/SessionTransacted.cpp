/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/SessionTransacted.cpp
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
#include "SessionTransacted.h"

#include "exception/LMDBException.h"

#include "log/LogLevel.h"
#include <commonlib/commonlib.h>
#include <sqlite3.h>
#include "Connection.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection){
	IAS_TRACER;

	beginTxnIfNeed();
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;

  if(!txn)
    return;

	int rc = mdb_txn_commit(txn);
  LMDBException::ThrowOnError("mdb_txn_commit", rc);

  txn = 0;

}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;

  if(!txn)
    return;

  mdb_txn_abort(txn);

  txn = 0;
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
}
}
}
}
