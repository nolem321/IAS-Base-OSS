/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/MatchExecute.cpp
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
#include "MatchExecute.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <qs/workers/proc/io/Output.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"
#include "../ProgramProvider.h"

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
MatchExecute::MatchExecute(const ::org::invenireaude::qsystem::workers::logic::MatchExecute* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
	Execute(dmParameters, pWorkContextManager){
	IAS_TRACER;

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}
}
/*************************************************************************/
MatchExecute::~MatchExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void MatchExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	      DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==MatchExecute starts: "<<dmData->getType()->getFullName());

	ptrProgramSet->execute(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==MatchExecute ends.");
}
/*************************************************************************/
}
}
}
}
}
