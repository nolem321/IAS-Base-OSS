/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/Browser.cpp
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
#include "Browser.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Session.h"
#include "System.h"
#include "Connection.h"
#include "Driver.h"

namespace IAS {
namespace QS {
namespace SDF {

/*************************************************************************/
Browser::Browser(Session* pSession, const API::Destination& refDestination):
	Receiver(pSession){
	IAS_TRACER;

	pDriver=getSession()->getConnection()->getSystem()->getBrowserDriver(refDestination);
	IAS_CHECK_IF_NULL(pDriver);
}

/*************************************************************************/
Browser::~Browser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
unsigned int Browser::skip(unsigned int iOffset){
	IAS_TRACER;
	return pDriver->skip(iOffset);
}
/*************************************************************************/
}
}
}
