/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/SharedBrowserInput.cpp
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
#include "SharedBrowserInput.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "SharedBrowserWorker.h"

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {
/*************************************************************************/
SharedBrowserInput::Workers SharedBrowserInput::TheWorkers(false);
/*************************************************************************/
SharedBrowserInput::SharedBrowserInput(const ::org::invenireaude::qsystem::workers::io::SharedBrowserInput* dmParameters,
									   WCM::WorkContextManager* pWorkContextManager):
		Common(dmParameters,pWorkContextManager){

	IAS_TRACER;

	Mutex::Locker locker(TheWorkers.mutex);
	if(TheWorkers.hmWorkersMap.count(dmParameters->getInputName()) == 0){
		TheWorkers.hmWorkersMap[dmParameters->getInputName()]
		   = IAS_DFT_FACTORY<SharedBrowserWorker>::Create(dmParameters);
		TheWorkers.hmWorkersMap[dmParameters->getInputName()]->start();
	}

	pWorker=TheWorkers.hmWorkersMap[dmParameters->getInputName()];
	pWorker->addReader();
}
/*************************************************************************/
SharedBrowserInput::~SharedBrowserInput() throw(){
	IAS_TRACER;

	if(pWorker->removeReader()){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Removing reader.");

		pWorker->stop();
		pWorker->join();
	}
}
/*************************************************************************/
API::Message* SharedBrowserInput::get(API::Attributes* pAttributes, int iTimeout){
	IAS_TRACER;

	if(pAttributes)
		IAS_THROW(BadUsageException("Selector not supported for Shared/Parallel browsers."))

	return pWorker->getNextMessage((iTimeout == Input::CDefaultTimeout ? this->iTimeout : iTimeout));
}
/*************************************************************************/
}
}
}
}
}
