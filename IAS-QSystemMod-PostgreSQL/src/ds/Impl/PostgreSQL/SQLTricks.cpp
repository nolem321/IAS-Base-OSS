/*
 * File: IAS-QSystemLib/src/ds/Impl/SQLTricks.cpp
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
#include "SQLTricks.h"

#include <commonlib/commonlib.h>
#include <qs/log/LogLevel.h>

#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {
/*************************************************************************/
SQLTricks::SQLTricks(){
	IAS_TRACER;
}
/*************************************************************************/
SQLTricks::~SQLTricks() throw(){
	IAS_TRACER;
}
/*************************************************************************/
bool SQLTricks::skipFunctionOutputParameters()const{
	return true;
}
/*************************************************************************/
String SQLTricks::makeProcedureCall(const String& strSQLText)const{
  return "SELECT " + strSQLText;
}
/*************************************************************************/
String SQLTricks::makeFunctionCall(const String& strSQLText)const{
  return ""+strSQLText;
}
/*************************************************************************/
}
}
}
}