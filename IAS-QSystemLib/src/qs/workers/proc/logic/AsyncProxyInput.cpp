/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/AsyncProxyInput.cpp
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
#include "AsyncProxyInput.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
AsyncProxyInput::AsyncProxyInput(const ::org::invenireaude::qsystem::workers::logic::AsyncProxyInput* dmParameters,
					 WCM::WorkContextManager* pWorkContextManager):
		LogicBase(dmParameters,pWorkContextManager){
	IAS_TRACER;
}
/*************************************************************************/
AsyncProxyInput::~AsyncProxyInput() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void AsyncProxyInput::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	try{

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==AsyncProxyInput starts.");

	//TODO Context preservation
	//TODO use logic settings for input/output
	//TODO getInput name? for the default output

	Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

	for(int iIdx=0; iIdx < lstAttributes.size(); iIdx++)
		if(lstAttributes.at(iIdx)->getName().compare(API::Attributes::CA_ReplyTo) == 0){
			Attribute* pAttribute=dmContext->createAttributes();
			pAttribute->setName("IAS_PROXY_RTY");
			pAttribute->setValue(lstAttributes.at(iIdx)->getValue());
			break;
		}


		pWorkContextManager->getIOManager()->getOutput("output")->send(dmContext,dmData);
	}catch(Exception& e){
		tryError(dmContext,dmData,e);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==AsyncProxyInput ends.");
}
/*************************************************************************/
void AsyncProxyInput::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								 API::Message* pMessage){
	IAS_TRACER;

	try{
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==AsyncProxyInput starts.");

		//TODO Context preservation
		//TODO use logic settings for input/output
		//TODO getInput name? for the default output

		Ext::AttributeList& lstAttributes(dmContext->getAttributesList());

		for(int iIdx=0; iIdx < lstAttributes.size(); iIdx++)
		if(lstAttributes.at(iIdx)->getName().compare(API::Attributes::CA_ReplyTo) == 0) {
			Attribute* pAttribute=dmContext->createAttributes();
			pAttribute->setName("IAS_PROXY_RTY");
			pAttribute->setValue(lstAttributes.at(iIdx)->getValue());
			break;
		}


		pWorkContextManager->getIOManager()->getOutput("output")->send(dmContext,*pMessage->getContent());
	}catch(Exception& e){
		tryError(dmContext,pMessage,e);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==AsyncProxyInput ends.");
}
/*************************************************************************/
}
}
}
}
}
