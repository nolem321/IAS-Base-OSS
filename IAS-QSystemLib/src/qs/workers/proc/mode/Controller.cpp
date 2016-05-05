/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/Controller.cpp
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
#include "Controller.h"
#include<qs/log/LogLevel.h>

#include "../GlobalContext.h"

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/InputSpecification.h>
#include <org/invenireaude/qsystem/workers/logic/LogicSpecification.h>
#include <org/invenireaude/qsystem/workers/logic/Logic.h>

#include <qs/Impl/Environment.h>

#include "../GlobalContext.h"
#include "Controller.h"

using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {

/*************************************************************************/
Controller::Controller(GlobalContext* pGlobalContext):
		pGlobalContext(pGlobalContext){
	IAS_TRACER;

}
/*************************************************************************/
Controller::~Controller() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Controller::start(){

	IAS_TRACER;

	unsigned int iNumThreads = 0;

	//TODO is this OFFSET used anywhere ?

	const spec::Specification *dmSpecification=pGlobalContext->getSpecification();

	unsigned int iOffSet     = dmSpecification->getInputSpec()->getOffset();
	unsigned int iNumMsgs    = dmSpecification->getInputSpec()->getNumMsgs();

	if(iNumThreads > 1 && iOffSet > 0)
		IAS_THROW(InternalException("Offset is supported only in a single threaded setup."));


	//Intialize before thread starts.
	IAS::InstanceFeature<QS::Impl::Environment>::GetInstance();

	IAS_DFT_FACTORY<ModeBase>::PtrHoldersCollection phcProcessors;

	SYS::Signal::GetInstance();

	const logic::Ext::LogicList& lstLogics(dmSpecification->getLogicSpec()->getLogicsList());

	for(int iIdx=0;iIdx<lstLogics.size();iIdx++){

		int iNumInstances=lstLogics.at(iIdx)->getInstances();
		while(iNumInstances-- > 0)
			phcProcessors.addPointer(createProcessor(iIdx));
	}


	for(IAS_DFT_FACTORY<ModeBase>::PtrHoldersCollection::iterator it=phcProcessors.begin();
			it != phcProcessors.end(); it++){
		(*it)->start();
	}

	for(IAS_DFT_FACTORY<ModeBase>::PtrHoldersCollection::iterator it=phcProcessors.begin();
			it != phcProcessors.end(); it++){
		(*it)->join();
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"*** Joined all threads ***");

	//TODO czy to jest potrzebne i kedy i w jakim watku ?
	//QS::Impl::Environment::Delete();
}
/*************************************************************************/
}
}
}
}
}
