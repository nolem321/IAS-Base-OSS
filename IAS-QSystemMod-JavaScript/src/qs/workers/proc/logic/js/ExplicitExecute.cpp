/*
 * File: IAS-QSystemMod-JavaScript/src/qs/workers/proc/logic/js/ExplicitExecute.cpp
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
#include <errno.h>

#include "ExplicitExecute.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

#include "exception/JavaScriptException.h"

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

#include "Context.h"
#include "Execution.h"

#include "JSString.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace JS{



/*************************************************************************/
ExplicitExecute::ExplicitExecute(
		::org::invenireaude::qsystem::workers::logic::External* dmParameters,
		WCM::WorkContextManager* pWorkContextManager) :
		LogicBase(dmParameters,pWorkContextManager) {
	IAS_TRACER;


	ptrContext=IAS_DFT_FACTORY<Context>::Create();

	ptrExecution=IAS_DFT_FACTORY<Execution>::Create(ptrContext.getPointer());

	ptrJSONHelper=IAS_DFT_FACTORY<DM::JSON::JSONHelper>::Create(this->pWorkContextManager->getGlobalContext()->getDataFactory());

	const DM::Default::Ext::StringList& lstScripts(dmParameters->getArgsList());

	if(lstScripts.size() == 0)
		IAS_THROW(JavaScriptException("At least one script name expected."));

	for(int iIdx=0; iIdx<lstScripts.size();iIdx++)
		ptrExecution->load(lstScripts.at(iIdx));

}
/*************************************************************************/
ExplicitExecute::~ExplicitExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ExplicitExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute starts.");

	StringStream ssContext;
	StringStream ssInput;
	StringStream ssOutput;

	JSString strCtx(ptrContext->getJSContext());
	JSString strInput(ptrContext->getJSContext());

	ptrJSONHelper->save(ssContext,dmContext);
	strCtx=ssContext.str();

	ptrJSONHelper->save(ssInput,dmData);
	strInput=ssInput.str();

	ssContext.str("");ssContext.clear();

	if(ptrExecution->run(strCtx, strInput, ssContext, ssOutput)){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"output:"<<ssContext.str());
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"output:"<<ssOutput.str());

		dmData=ptrJSONHelper->load(ssOutput);
		dmContext=::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContextType()->cast(ptrJSONHelper->load(ssContext));
		pWorkContextManager->getIOManager()->getDefaultOutput()->send(dmContext,dmData);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute ends.");
}
/*************************************************************************/
void ExplicitExecute::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
							 API::Message* pMessage){

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute starts.");

	StringStream ssContext;
	StringStream ssInput;
	StringStream ssOutput;

	JSString strCtx(ptrContext->getJSContext());
	JSString strInput(ptrContext->getJSContext());

	ptrJSONHelper->save(ssContext,dmContext);
	strCtx=ssContext.str();

	strInput.load(*pMessage->getContent());

	ssContext.str("");ssContext.clear();

	if(ptrExecution->run(strCtx, strInput, ssContext, ssOutput)){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"output:"<<ssContext.str());
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isData(),"output:"<<ssOutput.str());

		dmContext=::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContextType()->cast(ptrJSONHelper->load(ssContext));

		pWorkContextManager->getIOManager()->getDefaultOutput()->send(dmContext,ssOutput);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"==ExplicitExecute ends.");

}
/*************************************************************************/
}
}
}
}
}
}
//TODO json compatibility issues [] : {"attributes": [] }

/*************************************************************************/
extern "C"{
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_logic_js(::org::invenireaude::qsystem::workers::logic::External*    dmParameters,
											   ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){

	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::JS::ExplicitExecute>::
			Create(dmParameters,pWorkContextManager);
  }

}
