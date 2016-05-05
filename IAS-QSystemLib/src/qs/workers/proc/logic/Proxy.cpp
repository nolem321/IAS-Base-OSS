/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/Proxy.cpp
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
#include "Proxy.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include "../GlobalContext.h"

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
Proxy::Proxy(const ::org::invenireaude::qsystem::workers::logic::Proxy* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters,pWorkContextManager){
	IAS_TRACER;

}
/*************************************************************************/
Proxy::~Proxy() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Proxy::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Proxy starts.");

	//TODO use logic settings for input/output
	//TODO getInput name? for the default output

	Ext::ContextPtr dmContextTmp=dmContext->duplicateContext();

	pWorkContextManager->getIOManager()->getOutput("output")->send(dmContextTmp,dmData);

	Ext::ContextPtr dmContextMatch(DataFactory::GetInstance()->getContextType()->createContext());

	if(dmContext->isSetMID())
		dmContextMatch->setMID(dmContext->getMID());

	try{

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"= Proxy receiving ...");
		pWorkContextManager->getIOManager()->getInput("output")->receive(dmContextMatch,dmData);
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"= Proxy sending ...");
		pWorkContextManager->getIOManager()->getOutput("input")->send(dmContext,dmData);

	}catch(Exception& e){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"= Proxy error ...");
		tryError(dmContext,dmData,e);
	}


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Proxy ends.");
}
/*************************************************************************/
void Proxy::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					  API::Message* pMessage){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Proxy starts.");

	//TODO use logic settings for input/output
	//TODO getInput name? for the default output

	Ext::ContextPtr dmContextTmp=dmContext->duplicateContext();

	pWorkContextManager->getIOManager()->getOutput("output")->send(dmContextTmp,*pMessage->getContent());

	Ext::ContextPtr dmContextMatch(DataFactory::GetInstance()->getContextType()->createContext());

	Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	for(int iIdx=0; iIdx < lstAttributes.size(); iIdx++)
			if(lstAttributes.at(iIdx)->getName().compare(API::Attributes::CA_MID) == 0){
				Attribute* pAttribute=dmContextMatch->createAttributes();
				pAttribute->setName(API::Attributes::CA_CID);
				pAttribute->setValue(lstAttributes.at(iIdx)->getValue());
				break;
			}

	try{

		API::Message::PtrHolder ptrMessage;
		pWorkContextManager->getIOManager()->getInput("output")->receive(dmContextMatch,ptrMessage);
		pWorkContextManager->getIOManager()->getOutput("input")->send(dmContext,*ptrMessage->getContent());

	}catch(Exception& e){
		tryError(dmContext,pMessage,e);
	}


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==Proxy ends.");
}
/*************************************************************************/
}
}
}
}
}

