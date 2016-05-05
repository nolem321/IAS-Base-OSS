/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/SessionTransacted.cpp
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
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Connection.h"
#include "shared/SessionTable.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
SessionTransacted::SessionTransacted(Connection* pConnection):
	Session(pConnection->getAttachment()->getSessionTable()->createAutoCommit(),
	pConnection){
	IAS_TRACER;
}
/*************************************************************************/
SessionTransacted::~SessionTransacted() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void SessionTransacted::commit(){
	IAS_TRACER;
	ptrSession->commit();
}
/*************************************************************************/
void SessionTransacted::rollback(){
	IAS_TRACER;
	ptrSession->rollback();
}
/*************************************************************************/
Session::TransactionMode SessionTransacted::getMode()const{
	return Session::SM_Transacted;
}
/*************************************************************************/
}
}
}
