/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/Execute.cpp
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
#include "Execute.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <dm/datamodel.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
Execute::Execute(const ::org::invenireaude::qsystem::workers::logic::Execute* dmParameters,
				WCM::WorkContextManager* pWorkContextManager):
			    LogicBase(dmParameters,pWorkContextManager){
	IAS_TRACER;

	const DM::DataFactory* pDataFactory = pWorkContextManager->getGlobalContext()->getDataFactory();

	IAS_DFT_FACTORY<Prog::ResultHandlerForIO>::PtrHolder ptrResultHandler(
			IAS_DFT_FACTORY<Prog::ResultHandlerForIO>::Create(pDataFactory,this));

	ptrProgramSet=IAS_DFT_FACTORY<Prog::ProgramSet>::Create(pDataFactory,ptrResultHandler.pass());

}
/*************************************************************************/
Execute::~Execute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
}
