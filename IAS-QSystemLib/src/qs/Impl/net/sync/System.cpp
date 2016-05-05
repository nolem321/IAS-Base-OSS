/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/System.cpp
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
#include "System.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/ssl.h>

#include "Connection.h"
#include "org/invenireaude/qsystem/stats/DataFactory.h"
#include "BlockIOWrapperFactory.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
System::System(){
	IAS_TRACER;
	IAS::Net::SSL::Environment::GetInstance();
}
/*************************************************************************/
API::Connection* System::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	URI uri;
	API::Environment::BuildURI(uri,dmConnection);

	String key(uri.getURIString());

	if(hmBlockIOWrapperFactory.count(key) == 0)
		hmBlockIOWrapperFactory[key]=createBlockIOWrapperFactory(dmConnection);

	BlockIOWrapperFactory *pBlockIOWrapperFactory=hmBlockIOWrapperFactory.at(key);

	return IAS_DFT_FACTORY<Connection>::Create(this,pBlockIOWrapperFactory);

}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Net instance destroyed.");
}
/*************************************************************************/
}
}
}
}
