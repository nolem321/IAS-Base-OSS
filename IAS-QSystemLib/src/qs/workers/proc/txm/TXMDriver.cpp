/*
 * File: IAS-QSystemLib/src/qs/workers/proc/txm/TXMDriver.cpp
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
#include "TXMDriver.h"
#include<qs/log/LogLevel.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

using namespace org::invenireaude::qsystem::workers;
namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace TXM {

/*************************************************************************/
TXMDriver::TXMDriver(const ::org::invenireaude::qsystem::workers::txm::Parameter* dmParameter,
					 WCM::WorkContextManager* pWorkContextManager):
		pWorkContextManager(pWorkContextManager),
		dmParameter(dmParameter->duplicateParameter()){
	IAS_TRACER;

	//TODO Parameter to URI - mapper ?

	const Connection *dmConnection=dmParameter->getConnection();

	uriConnectionKey.setProtocol(dmConnection->getProtocol());

	if(dmConnection->isSetHost())
		uriConnectionKey.setHost(dmConnection->getHost());

	if(dmConnection->isSetUser())
		uriConnectionKey.setUser(dmConnection->getUser());

	if(dmConnection->isSetLocation())
		uriConnectionKey.setPath(dmConnection->getLocation());

	if(dmConnection->isSetPort())
			uriConnectionKey.setPort(dmConnection->getPort());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Driver: "<<uriConnectionKey.getURIString());
}
/*************************************************************************/
TXMDriver::~TXMDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
::IAS::TXM::API::Session*  TXMDriver::getSession(){
	IAS_TRACER;
	return pWorkContextManager->txm.lookupSession(uriConnectionKey);
}
/*************************************************************************/
}
}
}
}
}
