/*
 * File: Connector.cpp
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

#include "Connector.h"

#include <qs/workers/proc/wcm/Registry.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

using namespace IAS::QS::Workers::Proc::WCM;
namespace IAS {
namespace Tools {
namespace LDAP {

/*************************************************************************/
Connector::Connector(const String& strName):
	strName(strName){
	IAS_TRACER;

	const org::invenireaude::qsystem::workers::Connection* pConnection = Registry::GetInstance()->apps.lookup(strName);

	if(pConnection->getProtocol().compare("ldap") != 0)
		IAS_THROW(BadUsageException("LDAP connection expected for: " + strName));

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Connecting to: "<<pConnection->getHost()<<":"<<pConnection->getPort());


}
/*************************************************************************/
Connector::~Connector() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Connector::query(const String& strQuery, StringList& lstResult){
	IAS_TRACER;

	lstResult.push_back("result 1");
	lstResult.push_back("result 2");

}
/*************************************************************************/
}
}
}
