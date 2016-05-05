/*
 * File: IAS-QSystemLib/src/qs/api/Environment.cpp
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
#include "Environment.h"
#include<qs/log/LogLevel.h>
#include <qs/Impl/Environment.h>

#include "org/invenireaude/qsystem/workers/DataFactory.h"


namespace IAS {
namespace QS {
namespace API {

/*************************************************************************/
Environment* Environment::GetInstance() {

	return InstanceFeature<Impl::Environment>::GetInstance();

};
/*************************************************************************/
void Environment::BuildURI(URI& uri, const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	if(dmConnection->isSetProtocol())
		uri.setProtocol(dmConnection->getProtocol());

	if(dmConnection->isSetPort())
		uri.setPort(dmConnection->getPort());

	if(dmConnection->isSetHost())
		uri.setHost(dmConnection->getHost());
}
/*************************************************************************/
::org::invenireaude::qsystem::workers::Ext::ConnectionPtr Environment::BuildConnection(const String& strProtocol,
														  	  	  	          const String& strHost,
																	          int iPort){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::ConnectionPtr dmConnection(
				::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createConnection());

	dmConnection->setProtocol(strProtocol);
	dmConnection->setHost(strHost);
	if(iPort > 0)
		dmConnection->setPort(iPort);

	return dmConnection;
}
/*************************************************************************/
}
}
}

