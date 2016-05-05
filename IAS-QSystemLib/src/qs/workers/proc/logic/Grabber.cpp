/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/Grabber.cpp
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
#include "Grabber.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
Grabber::Grabber(const ::org::invenireaude::qsystem::workers::logic::Grabber* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters, pWorkContextManager){
	IAS_TRACER;

	//TODO non dm parsing mode
	if(dmParameters->isSetParseDM() && !dmParameters->getParseDM())
		IAS_THROW(BadUsageException("DM parsing must be enabled for Grabber Logic."))


	strGrabberInput=dmParameters->getGrabberInput();
}
/*************************************************************************/
Grabber::~Grabber() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Grabber::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Grabber starts.");

	//TODO Context preservation
	//TODO getInput name? for the default output

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContextTmp=dmContext->duplicateContext();

	try{

		while(true){
			pWorkContextManager->getIOManager()->getInput(strGrabberInput)->receive(dmContextTmp,dmData);
			pWorkContextManager->getIOManager()->getOutput("input")->send(dmContext,dmData);
		}

	}catch(EndOfDataException& e){

	}catch(Exception& e){
		//TODO error handling
		dmData=pWorkContextManager->getGlobalContext()->getDataFactory()->
				getDefaultType(DM::Type::TextType)->createDataObject(e.toString());
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Grabber ends.");
}
/*************************************************************************/
}
}
}
}
}
