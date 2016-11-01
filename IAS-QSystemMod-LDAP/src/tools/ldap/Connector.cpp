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
	strName(strName),
	bValid(false){
	IAS_TRACER;

    dmConnection = Registry::GetInstance()->apps.lookup(strName)->duplicateConnection();

    if(dmConnection->getProtocol().compare("ldap") != 0) {
      IAS_THROW(BadUsageException("LDAP connection expected for: " + strName));
    }

    connect();
}
/*************************************************************************/
Connector::~Connector() throw(){
	IAS_TRACER;
 }
/*************************************************************************/
void Connector::query(const String& strSearchBase, const String& strQuery, EntryList& lstResult){
	IAS_TRACER;
  
	Mutex::Locker locker(mutex);

	if(!bValid)
		connect();

	bValid = false;

	IAS_DFT_FACTORY<Handle::QueryResult>::PtrHolder ptrQueryResult(
			ptrConnection->query(strSearchBase, strQuery));

	ptrQueryResult->getEntries(lstResult);

	bValid = true;
}
/*************************************************************************/
void Connector::connect(){
	IAS_TRACER;

	ptrConnection = IAS_DFT_FACTORY<Handle::Connection>::Create(dmConnection->getHost(), dmConnection->getPort());
	ptrConnection->setProtocol();
	ptrConnection->authorize(dmConnection->getUser(), dmConnection->getPassword());


	bValid = true;
}
/*************************************************************************/
}
}
}
