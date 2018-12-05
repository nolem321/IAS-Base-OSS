/*
 * File: IAS-QSystemLib/src/ds/Impl/Session.cpp
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
#include <qs/log/LogLevel.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

#include "Connection.h"
#include "SQLTricks.h"
#include "System.h"

namespace IAS {
namespace DS {
namespace Impl {

/*************************************************************************/
Session::ObjectModeNamesMap::ObjectModeNamesMap(){
	(*this)["BINARY"] = DS::API::Environment::OM_BINARY;
	(*this)["TEXT"]   = DS::API::Environment::OM_TEXT;
	(*this)["BLOB"]   = DS::API::Environment::OM_BLOB;
	(*this)["CLOB"]   = DS::API::Environment::OM_CLOB;
}
/*************************************************************************/
const Session::ObjectModeNamesMap Session::hmObjectModeNames;
/*************************************************************************/
Session::Session(Connection* pConnection):
		pConnection(pConnection),
		iObjectMode(DS::API::Environment::OM_TEXT){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pConnection);

	String strFormatter("JSON");

	if(pConnection->getParameter()->isSetObjectFormatter())
		strFormatter=pConnection->getParameter()->getObjectFormatter();

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Fmt:["<<strFormatter<<"]");
	pFormatter=pConnection->getSystem()->getFmtFactory()->getFormatter(strFormatter);

	if(pConnection->getParameter()->isSetObjectMode())
		iObjectMode = parseObjectMode(pConnection->getParameter()->getObjectMode());

}
/*************************************************************************/
Session::~Session() throw(){
	IAS_TRACER;
	IAS_LOG(::IAS::QS::LogLevel::INSTANCE.bIsInfo,"DS Session cleanup.")
}
/*************************************************************************/
DS::API::Environment::ObjectMode Session::getObjectMode()const{
	return iObjectMode;
}
/*************************************************************************/
DS::API::Environment::ObjectMode Session::parseObjectMode(const String& strValue){
	IAS_TRACER;

	ObjectModeNamesMap::const_iterator it = hmObjectModeNames.find(MiscTools::StrToUpper(strValue));

	if(it == hmObjectModeNames.end())
		IAS_THROW(ItemNotFoundException(String("ObjectMode: ") + strValue));

	return it->second;
}
/*************************************************************************/
const API::SQLTricks* Session::getSQLTricks()const{
  return pConnection->getSystem()->getSQLTricks();
}
/*************************************************************************/

}
}
}
