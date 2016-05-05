/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Manageable.cpp
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
#include "Manageable.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Session.h"
#include "Connection.h"
#include "System.h"

#include <qs/Impl/net/pump/MsgPumpFactory.h>

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
Manageable::Manageable(Session* pSession):
		pSession(pSession){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSession)

	pMsgPumpFactory=pSession->getConnection()->getSystem()->getPumpFactory();

}

/*************************************************************************/
Manageable::~Manageable() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
