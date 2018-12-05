/*
 * File: IAS-QSystemMod-LMDB/src/ds/Impl/LMDB/Statement.cpp
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
#include "exception/LMDBException.h"
#include "log/LogLevel.h"
#include <sqlite3.h>

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace LMDB {

/*************************************************************************/
Statement::Statement(Session* pSession):pSession(pSession){
	IAS_TRACER;
}
/*************************************************************************/
Statement::~Statement() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Statement::setSQLText(const String& strSQLText){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"setSQL:["<<strSQLText<<"]");
  this->strSQLText = strSQLText;
}
/*************************************************************************/
void Statement::prepare(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
