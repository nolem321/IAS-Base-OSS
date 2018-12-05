/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/Session.cpp
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
#include "Session.h"

#include <commonlib/commonlib.h>
#include "log/LogLevel.h"
#include "Connection.h"
#include "System.h"
#include "StatementInsert.h"
#include "StatementSelect.h"
#include "StatementDelete.h"
#include "StatementUpdate.h"

#include "exception/LMDBException.h"

#include <qs/fmt/FmtFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
Session::Session(Connection* pConnection):
  Impl::Session(pConnection),
	pConnection(pConnection),
	txn(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pConnection);

	String strConnection(EnvTools::Substitute(pConnection->getParameter()->getConnection()->getLocation()));

  MDB_env *env = pConnection->getSystem()->getEnv();

	int rc = mdb_env_open(env, strConnection.c_str(), 0, 0664);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"opening:["<<strConnection<<"], rc="<<rc);
	LMDBException::ThrowOnError("mdb_env_open" + pConnection->getName(),rc);

  rc = mdb_txn_begin(env, NULL, 0, &txn);
  LMDBException::ThrowOnError("mdb_txn_begin" + pConnection->getName(),rc);

  rc = mdb_open(txn, NULL, 0, &dbi);
  LMDBException::ThrowOnError("mdb_txn_begin" + pConnection->getName(),rc);


}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
  MDB_env *env = pConnection->getSystem()->getEnv();

  if(txn)
    mdb_txn_abort(txn);

	mdb_close(env, dbi);
}
/*************************************************************************/
Connection* Session::getConnection()const{
	IAS_TRACER;
	return pConnection;
}
/*************************************************************************/
API::StatementInsert*  Session::createInsert(){
	return IAS_DFT_FACTORY<StatementInsert>::Create(this);
}

/*************************************************************************/
API::StatementSelect*  Session::createSelect(){
	return IAS_DFT_FACTORY<LMDB::StatementSelect>::Create(this);
}
/*************************************************************************/
API::StatementCall*  Session::createCall(){
	IAS_THROW(LMDBException("Stored procedures are not available in LMDB."));
}
/*************************************************************************/
API::StatementFunCall*  Session::createFunCall(){
	IAS_THROW(LMDBException("Stored procedures are not available in LMDB."));
}
/*************************************************************************/
API::StatementDelete*  Session::createDelete(){
	return IAS_DFT_FACTORY<LMDB::StatementDelete>::Create(this);
}
/*************************************************************************/
API::StatementUpdate*  Session::createUpdate(){
	return IAS_DFT_FACTORY<LMDB::StatementUpdate>::Create(this);
}
/*************************************************************************/
void Session::beginTxnIfNeed(){
	IAS_TRACER;

  if(txn)
    return;

  MDB_env *env = pConnection->getSystem()->getEnv();
  int rc = mdb_txn_begin(env, NULL, 0, &txn);
  LMDBException::ThrowOnError("mdb_txn_begin" + pConnection->getName(),rc);

}
/*************************************************************************/

}
}
}
}

