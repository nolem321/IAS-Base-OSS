/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/Registry.cpp
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
#include "Registry.h"

#include<qs/log/LogLevel.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>


#include <org/invenireaude/qsystem/workers/io/Registry.h>
#include <org/invenireaude/qsystem/workers/ds/Registry.h>
#include <org/invenireaude/qsystem/workers/ec/Registry.h>
#include <org/invenireaude/qsystem/workers/spec/Registry.h>
#include <org/invenireaude/qsystem/workers/spec/DataFactory.h>

#include <dm/datamodel.h>

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
/*************************************************************************/
const String& Registry::CStrEnvName("IAS_QS_REGISTRY");
/*************************************************************************/
Registry::Registry(){
	IAS_TRACER;

	pDataFactory=workers::DataFactory::GetInstance()->getContaingDataFactory();

	loadRegistry();

}
/*************************************************************************/
Registry::~Registry() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void Registry::loadRegistry(){
	IAS_TRACER;

	StringList lstFiles;
	EnvTools::GetEnvTokenized(CStrEnvName,lstFiles);

	for (StringList::const_iterator it=lstFiles.begin(); it != lstFiles.end(); ++it) {
		loadRegistry(*it);
	}

}
/*************************************************************************/
void Registry::loadRegistry(const String& strFileName){
	IAS_TRACER;

	IAS_DFT_FACTORY<DM::XML::XMLHelper>::PtrHolder ptrHelper(
			IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(pDataFactory));

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrXMLDoc(
		ptrHelper->readFile(strFileName));

	workers::spec::Ext::RegistryPtr dmRegistry=workers::spec::DataFactory::GetInstance()->getRegistryType()->cast(ptrXMLDoc->getRootObject());

	if(dmRegistry->isSetDs())
		insertRegistry(dmRegistry->getDs(),ds);

	if(dmRegistry->isSetIo())
		insertRegistry(dmRegistry->getIo(),io);

	if(dmRegistry->isSetEc())
		insertRegistry(dmRegistry->getEc(),ecs);
}
/*************************************************************************/
void Registry::insertRegistry(const org::invenireaude::qsystem::workers::Registry* pRegistry,
		            RegistryMapping& mapping){
	IAS_TRACER;

	const workers::Ext::ConnectionList& lstConnections(pRegistry->getConnectionsList());

	for(int iIdx=0; iIdx<lstConnections.size();iIdx++)
		mapping.addConnection(lstConnections.at(iIdx));

}
/*************************************************************************/
const org::invenireaude::qsystem::workers::Connection* Registry::RegistryMapping::lookup(const String& strAlias)const{
	IAS_TRACER;

	Mutex::Locker locker(const_cast<RegistryMapping*>(this)->mutex);

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<strAlias);

	if(hmConnections.count(strAlias) == 0)
		IAS_THROW(ItemNotFoundException("Connection not found in the registry: ")<<strAlias);

	return hmConnections.at(strAlias);
}
/*************************************************************************/
void Registry::RegistryMapping::addConnection(const org::invenireaude::qsystem::workers::Connection* pConnection){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Adding: "<<pConnection->getAlias());

	if(!pConnection->isSetAlias())
		IAS_THROW(BadUsageException("Connection alias not specified."));

	if(hmConnections.count(pConnection->getAlias()))
		IAS_THROW(BadUsageException("Connection already exists in the registry: ")<<pConnection->getAlias());

	hmConnections[pConnection->getAlias()]=pConnection->duplicateConnection();

	String strAlias(pConnection->getAlias());

}
/*************************************************************************/
}
}
}
}
}
