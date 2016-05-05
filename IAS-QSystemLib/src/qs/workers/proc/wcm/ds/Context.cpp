/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/ds/Context.cpp
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
#include "../../wcm/ds/Context.h"
#include "../../wcm/ds/Context.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/ds/DSFactory.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include "../Registry.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace DS {

/************************************************************************/
::IAS::DS::API::Session* Context::lookupSession(URI& uri,
												const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	createEntryIfNeeded(uri,dmParameter);

	return hmSession.at(uri.getURIString())->ptrSession;
}
/*************************************************************************/
::IAS::DS::API::Connection* Context::lookupConnection(URI& uri, const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	createEntryIfNeeded(uri,dmParameter);

	return hmSession.at(uri.getURIString())->ptrConnection;
}
/*************************************************************************/
void Context::createEntryIfNeeded(URI& uri,const workers::ds::Parameter* dmParameter){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Check: "<<uri.getURIString());

	if(!dmParameter->isSetConnection())
		IAS_THROW(BadUsageException("No connection defined for the data source."));

	/*
	 * We have to build the parameters again as the registry may contain different values.
	 */

	workers::ds::Ext::ParameterPtr dmLocalParameter(dmParameter->duplicateParameter());

	if(uri.getProtocol().empty()){

		if((!dmLocalParameter->getConnection()->isSetProtocol() &&
			 dmLocalParameter->getConnection()->isSetAlias())
			||dmLocalParameter->getConnection()->getProtocol().compare("registry") == 0)

			dmLocalParameter->setConnection(Registry::GetInstance()->ds.lookup(dmLocalParameter->getConnection()->getAlias())->duplicateConnection());

		const workers::Connection *dmConnection=dmLocalParameter->getConnection();

		if(!dmConnection->isSetProtocol())
			IAS_THROW(BadUsageException("No connection protocol defined for the data source."));

		uri.setProtocol(dmConnection->getProtocol());

		if(dmConnection->isSetHost())
			uri.setHost(dmConnection->getHost());

		if(dmConnection->isSetUser())
			uri.setUser(dmConnection->getUser());

		if(dmConnection->isSetLocation())
			uri.setPath(dmConnection->getLocation());

	}


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Check updated: "<<uri.getURIString());

	if(hmSession.hasKey(uri.getURIString()))
		return;

	IAS_DFT_FACTORY<Entry>::PtrHolder ptrEntry(
						IAS_DFT_FACTORY<Entry>::Create());

	ptrEntry->ptrConnection=::IAS::DS::API::Environment::GetInstance()->connect(dmLocalParameter);

	ptrEntry->ptrSession=ptrEntry->ptrConnection->createSession(
			dmParameter->isSetTxnMode() ?
			Proc::DS::DSFactory::StringToTransactionMode(dmParameter->getTxnMode()) : IAS::DS::API::Session::SM_Transacted);

	hmSession[uri.getURIString()]=ptrEntry.pass();

}
/*************************************************************************/
void Context::commit(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"DS Committing ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++){

		if(it->second->ptrSession->getMode() == IAS::DS::API::Session::SM_Transacted)
			it->second->ptrSession->commit();
	}

}
/*************************************************************************/
void Context::rollback(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"DS Rolling back ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++){

		if(it->second->ptrSession->getMode() == IAS::DS::API::Session::SM_Transacted)
			it->second->ptrSession->rollback();
	}

}
/*************************************************************************/
}
}
}
}
}
}
