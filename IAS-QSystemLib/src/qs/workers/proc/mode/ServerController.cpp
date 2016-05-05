/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/ServerController.cpp
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
#include "ServerController.h"
#include<qs/log/LogLevel.h>

#include "../GlobalContext.h"

#include "Server.h"

using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {

/*************************************************************************/
ServerController::ServerController(GlobalContext* pGlobalContext):
	Controller(pGlobalContext){
	IAS_TRACER;
}
/*************************************************************************/
ServerController::~ServerController() throw(){
	IAS_TRACER;
}
/*************************************************************************/
ModeBase* ServerController::createProcessor(int iLogicIdx){

	IAS_TRACER;

	return IAS_DFT_FACTORY<Server>::Create(pGlobalContext,iLogicIdx);
}
/*************************************************************************/
}
}
}
}
}
