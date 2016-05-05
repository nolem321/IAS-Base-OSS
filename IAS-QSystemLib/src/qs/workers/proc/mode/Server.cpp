/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/Server.cpp
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
#include "Server.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../GlobalContext.h"
#include "../io/IOFactory.h"

#include <qs/Impl/Environment.h>

#include "../exception/RollbackMeException.h"
#include "AutoCancel.h"

#include "ProcessorWorker.h"

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {
/*************************************************************************/
Server::Server(GlobalContext *pGlobalContext,
    	 	 int iLogicIdx):
	ModeBase(pGlobalContext,iLogicIdx){
	IAS_TRACER;
}
/*************************************************************************/
Server::~Server() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Server::run(){
	IAS_TRACER;


	while(pGlobalContext->allDone() &&
			!SYS::Signal::GetInstance()->isStopping()) {

		AutoCancel ac(pGlobalContext);

		Thread::Cancellation tc(false);
		SYS::Signal::ThreadRegistration threadRegistration;

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Starting processor thread. ");

		IAS_DFT_FACTORY<ProcessorWorker>::PtrHolder ptrWorker;

		ptrWorker=IAS_DFT_FACTORY<ProcessorWorker>::Create(pGlobalContext,iLogicIdx);

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Starting: ");
		ptrWorker->iterate();

		ac.release();

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** End of work ! ");
	}

}
/*************************************************************************/
}
}
}
}
}
