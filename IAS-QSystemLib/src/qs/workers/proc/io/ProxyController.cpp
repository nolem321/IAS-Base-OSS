/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/ProxyController.cpp
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
#include "ProxyController.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {
/*************************************************************************/
ProxyController::ProxyController(Common* pCommon):pCommon(pCommon){

	ptrController=pCommon->getSession()->createController(pCommon->getDestination());
};
/*************************************************************************/
ProxyController::~ProxyController() throw(){};
/*************************************************************************/
unsigned int ProxyController::getNumMessages(){
	IAS_TRACER;

	return ptrController->getNumMessages();
}
/*************************************************************************/
}
}
}
}
}
