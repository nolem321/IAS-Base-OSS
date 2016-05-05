/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/server/System.cpp
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

#include "BlockIOWrapperFactory.h"
#include "ssl/BlockIOWrapperFactory.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync {
namespace Server {

/*************************************************************************/
System::System():IAS::QS::Net::Sync::System(){
	IAS_TRACER;
}
/*************************************************************************/
System::~System() throw () {
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Net server instance destroyed.");
}
/*************************************************************************/
Sync::BlockIOWrapperFactory* System::createBlockIOWrapperFactory(const ::org::invenireaude::qsystem::workers::Connection* dmConnection)const{
	IAS_TRACER;
	if(dmConnection->isSetSsl())
		return IAS_DFT_FACTORY<SSL::BlockIOWrapperFactory>::Create(dmConnection);
	else
		return IAS_DFT_FACTORY<BlockIOWrapperFactory>::Create(dmConnection);
}
/*************************************************************************/
}
}
}
}
}
