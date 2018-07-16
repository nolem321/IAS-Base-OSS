/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/RunExecute.cpp
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
#include "RunExecute.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"
#include "../ProgramProvider.h"

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <unistd.h>

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
RunExecute::RunExecute(const ::org::invenireaude::qsystem::workers::logic::RunExecute* dmParameters,
					 	 	 WCM::WorkContextManager* pWorkContextManager):
	Execute(dmParameters, pWorkContextManager),
	bDone(false){

	IAS_TRACER;

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}

	dmRunParameters =	::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->
				getRunParametersType()->createRunParameters();

	const DM::Default::Ext::StringList& lstParameters(dmParameters->getParametersList());

	for(int iIdx = 0; iIdx < lstParameters.size(); iIdx++)
		dmRunParameters->setArgs(EnvTools::Substitute(lstParameters.at(iIdx)));

	if(!isDM())
		IAS_LOG(QS::LogLevel::INSTANCE.isError(),"Parsing switch is ignored for the Run Execute Logic.");
}
/*************************************************************************/
RunExecute::~RunExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void RunExecute::receive(bool bNoWait){
	IAS_TRACER;

	if(bDone){
		this->pWorkContextManager->getGlobalContext()->abort();
		IAS_THROW(EndOfDataException());
	}

	bDone = true;
}
/*************************************************************************/
void RunExecute::compute(){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::Ext::RunParametersPtr dmLocalRunParamters
	 (dmRunParameters->duplicateRunParameters());

	TimeSample tsStart(true);

	workers::Ext::ContextPtr dmContext;
	dmContext = workers::DataFactory::GetInstance()->getContextType()->createContext();

	DM::DataObjectPtr dmValue(dmRunParameters);

	computeDM(dmContext, dmValue);

}
/*************************************************************************/
void RunExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==RunExecute starts.");

	ptrProgramSet->execute(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==RunExecute ends.");
}
/*************************************************************************/
}
}
}
}
}
