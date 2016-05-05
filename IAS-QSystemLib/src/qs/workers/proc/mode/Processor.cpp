/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/Processor.cpp
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
#include "Processor.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../GlobalContext.h"
#include "ProcessorWorker.h"

#include "AutoCancel.h"

#include <qs/ui/Messages.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {
/*************************************************************************/
Processor::Processor(GlobalContext *pGlobalContext,
     	 int iLogicIdx):
    ModeBase(pGlobalContext,iLogicIdx){
	IAS_TRACER;
}
/*************************************************************************/
Processor::~Processor() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Processor::run(){
	IAS_TRACER;

		AutoCancel ac(pGlobalContext);

		Thread::Cancellation tc(false);
		SYS::Signal::ThreadRegistration threadRegistration;

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Starting processor thread. ");

		IAS_DFT_FACTORY<ProcessorWorker>::PtrHolder ptrWorker;

		try{
			ptrWorker=IAS_DFT_FACTORY<ProcessorWorker>::Create(pGlobalContext,iLogicIdx);
		}catch(Exception& e){
			UserMessage(UI::Messages::MSGE_ConfigError)<<e.getName()<<e.getInfo();
			return;
		}

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Starting: ");

		UserMessage(UI::Messages::MSGI_LogicStarted)<<iLogicIdx;

		ptrWorker->iterate();
		ac.release();

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** End of work ! ");

		UserMessage(UI::Messages::MSGI_LogicStopped)<<iLogicIdx;
}
/*************************************************************************/
}
}
}
}
}
