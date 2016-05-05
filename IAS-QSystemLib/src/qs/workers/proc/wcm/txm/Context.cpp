/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/txm/Context.cpp
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
#include "../../wcm/txm/Context.h"
#include "../../wcm/txm/Context.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace TXM {

/************************************************************************/
IAS::TXM::API::Session* Context::lookupSession(const URI& uri){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Lookup: "<<uri.getURIString());

	if(!hmSession.hasKey(uri.getURIString()))
		createEntry(uri);

	Entry* pEntry=hmSession.at(uri.getURIString());

	if(!(pEntry->ptrSession))
			pEntry->ptrSession=pEntry->ptrConnection->createSession();

		return pEntry->ptrSession;

}
/*************************************************************************/
void Context::createEntry(const URI& uri){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"New: "<<uri.getProtocol()<<","<<uri.getHost());

	IAS_DFT_FACTORY<Entry>::PtrHolder ptrEntry(
						IAS_DFT_FACTORY<Entry>::Create());

	ptrEntry->ptrConnection=IAS::TXM::API::Environment::GetInstance()->connect(uri);

	hmSession[uri.getURIString()]=ptrEntry.pass();

}
/*************************************************************************/
void Context::begin(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," >> TXM Begin Transaction:"<<hmSession.size());

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++)
			it->second->ptrSession->begin();

}
/*************************************************************************/
void Context::commit(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"TXM Committing ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++)
			it->second->ptrSession->commit();

}
/*************************************************************************/
void Context::rollback(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"TXM Rolling back ... ");

	for(SessionsMap::iterator it=hmSession.begin();
		it!=hmSession.end(); it++)
			it->second->ptrSession->rollback();

}
/*************************************************************************/
}
}
}
}
}
}
