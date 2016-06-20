/*
 * File: IAS-QSystemLib/src/qs/workers/proc/prog/CallbackSet.cpp
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
#include "CallbackSet.h"

#include <qs/workers/proc/ProgramProvider.h>

#include "DefaultResultHandler.h"

using namespace ::org::invenireaude::qsystem::workers;
namespace IAS{
using namespace Lang;
namespace QS {
namespace Workers {
namespace Proc {
namespace Prog {

//TODO Add support for
// errorAction
// exact/match calls.
// copy ctx/data on input (exit cannot modify).

/*************************************************************************/
CallbackSet::CallbackSet(const ::IAS::DM::DataFactory *pDataFactory):
	ProgramSet(pDataFactory, IAS_DFT_FACTORY<DefaultResultHandler>::Create(pDataFactory)){

}
/*************************************************************************/
void CallbackSet::Build(ProgramSet      *pProgramSet,
		  	  	  	    ProgramProvider *pProgramProvider,
		  	  	  	    const ::org::invenireaude::qsystem::workers::Ext::CallbackList& lstParamters){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pProgramProvider);
	IAS_CHECK_IF_NULL(pProgramSet);

	for(int iIdx=0; iIdx<lstParamters.size(); iIdx++){
		const Callback *pCallback=lstParamters.at(iIdx);
		pProgramProvider->load(pCallback->getProgram(),pProgramSet);
	}
}
/*************************************************************************/
}
}
}
}
}
