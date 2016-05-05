/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/io/Context.cpp
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
#include "../../wcm/io/Context.h"
#include "../../wcm/io/Context.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

#include "../Registry.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace IO {

/************************************************************************/

static API::Session::TransactionMode _StringToTransactionMode(const String& strMode){

	//TODO add uppercase to String

	String strValue;
	for(String::const_iterator it=strMode.begin();it != strMode.end();it++)
		strValue+=(char)toupper(*it);

	if(!strValue.compare("TXN"))
		return API::Session::SM_Transacted;

	if(!strValue.compare("NONTXN"))
		return API::Session::SM_NonTransacted;

	if(!strValue.compare("XA"))
		return API::Session::SM_XAManaged;

	IAS_THROW(BadUsageException(String("Unknown session mode:")+strMode));
}
/*************************************************************************/
API::Session* Context::lookupSession(URI& uri,
										const ::org::invenireaude::qsystem::workers::io::Parameters* dmParameters){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	createEntryIfNeeded(uri,dmParameters->getConnection());

	Entry* pEntry=hmSession.at(uri.getURIString());

	API::Session::TransactionMode iMode = QS::API::Session::SM_NonTransacted;

	if(dmParameters->isSetTxnMode())
		iMode=_StringToTransactionMode(dmParameters->getTxnMode());

	switch(iMode){

	case QS::API::Session::SM_Transacted:
		if(!(pEntry->ptrTransactedSession))
			pEntry->ptrTransactedSession=pEntry->ptrConnection->createSession(iMode);

		return pEntry->ptrTransactedSession;

	case QS::API::Session::SM_NonTransacted:

			if(!(pEntry->ptrAutoCommitSession))
				pEntry->ptrAutoCommitSession=pEntry->ptrConnection->createSession(iMode);

			return pEntry->ptrAutoCommitSession;


	case QS::API::Session::SM_XAManaged:

		if(!(pEntry->ptrXAManagedSession))
			pEntry->ptrXAManagedSession=pEntry->ptrConnection->createSession(iMode);

		return pEntry->ptrXAManagedSession;

	default:
		IAS_THROW(BadUsageException(String("Unknown session transaction mode for: ")+uri.getURIString()));
	}
}
/*************************************************************************/
API::Connection* Context::lookupConnection(URI& uri,
		const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	createEntryIfNeeded(uri,dmConnection);

	return hmSession.at(uri.getURIString())->ptrConnection;
}
/*************************************************************************/
API::Administrator* Context::lookupAdministrator(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	createEntryIfNeeded(uri,dmConnection);

	if(! hmSession.at(uri.getURIString())->ptrAdministrator){

		hmSession[uri.getURIString()]->ptrAdministrator=
				lookupConnection(uri,dmConnection)->createAdministrator();
	}

	return hmSession.at(uri.getURIString())->ptrAdministrator;
}
/*************************************************************************/
void Context::createEntryIfNeeded(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	if(uri.getProtocol().empty()){

		if((!dmConnection->isSetProtocol() && dmConnection->isSetAlias())
				||dmConnection->getProtocol().compare("registry") == 0)
			dmConnection=Registry::GetInstance()->io.lookup(dmConnection->getAlias());

		QS:API::Environment::BuildURI(uri,dmConnection);
	}

	if(!hmSession.hasKey(uri.getURIString()))
		hmSession[uri.getURIString()]=IAS_DFT_FACTORY<Entry>::Create(dmConnection);
}
/*************************************************************************/
Context::Entry::Entry(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;
	ptrConnection=QS::API::Environment::GetInstance()->connect(dmConnection);
}
/*************************************************************************/
void Context::commit(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"QS Committing ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++){

		if(! it->second->ptrTransactedSession.isNull())
			it->second->ptrTransactedSession->commit();
	}

}
/*************************************************************************/
void Context::rollback(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"QS Rolling back ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++){

		if(! it->second->ptrTransactedSession.isNull())
			it->second->ptrTransactedSession->rollback();
	}

}
/*************************************************************************/
}
}
}
}
}
}
