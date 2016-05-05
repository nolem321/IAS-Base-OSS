/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/SessionAutoCommit.cpp
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
#include "SessionAutoCommit.h"
#include "log/LogLevel.h"
#include <commonlib/commonlib.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

/*************************************************************************/
SessionAutoCommit::SessionAutoCommit(Connection* pConnection):
	Session(pConnection){
	IAS_TRACER;
}

/*************************************************************************/
SessionAutoCommit::~SessionAutoCommit() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionAutoCommit::commit(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
void SessionAutoCommit::rollback(){
	IAS_TRACER;
	IAS_THROW(InternalException("TODO  not transacted  !"))
}
/*************************************************************************/
Session::TransactionMode SessionAutoCommit::getMode()const{
	return Session::SM_NonTransacted;
}
/*************************************************************************/
}
}
}
}
