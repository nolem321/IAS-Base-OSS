/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/client/BlockIOWrapperFactory.cpp
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
#include "BlockIOWrapperFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <org/invenireaude/qsystem/workers/ClientIP.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{
namespace Client {

/*************************************************************************/
BlockIOWrapperFactory::BlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
		Sync::BlockIOWrapperFactory(dmConnection),
		IAS::Net::Client(IAS::Net::Peer(dmConnection->getHost(), dmConnection->isSetPort() ? dmConnection->getPort() : 50000)){
	IAS_TRACER;

	if(dmConnection->isSetClient()){
		String strLocalInterface;
		String strLocalPort;

		if(dmConnection->getClient()->isSetInterface())
			strLocalInterface=dmConnection->getClient()->getInterface();

		if(dmConnection->getClient()->isSetPort())
			strLocalPort=dmConnection->getClient()->getPort();

		IAS::Net::Peer peerLocal(strLocalInterface,strLocalPort);
		setLocalPeer(peerLocal);
	}

}
/*************************************************************************/
BlockIOWrapperFactory::~BlockIOWrapperFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Sync::BlockIOWrapper* BlockIOWrapperFactory::createBlockIOWrapper()const{
	IAS_TRACER;
	return IAS_DFT_FACTORY<BlockIOWrapper>::Create(connect());
}
/*************************************************************************/
}
}
}
}
}
