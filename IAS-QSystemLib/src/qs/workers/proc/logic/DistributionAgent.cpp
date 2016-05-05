/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/DistributionAgent.cpp
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
#include "DistributionAgent.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Input.h>
#include <qs/workers/proc/io/ProducerOutput.h>
#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>

#include <qs/workers/proc/exception/RollbackMeException.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"

#include "../io/BrowserInput.h"

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
DistributionAgent::DistributionAgent(const ::org::invenireaude::qsystem::workers::logic::DistributionAgent* dmParameters,
							  WCM::WorkContextManager* pWorkContextManager):
		strAttribute("DST"),
			LogicBase(dmParameters,pWorkContextManager){

	IAS_TRACER;

	if(dmParameters->isSetAttribute())
		strAttribute=dmParameters->getAttribute();

	dmProducerOutput = workers::io::DataFactory::GetInstance()->createProducerOutput();

	if(dmParameters->isSetConnection())
		dmProducerOutput->setConnection(dmParameters->getConnection()->duplicateConnection());

	dmProducerOutput->setTxnMode("NONTXN");

}
/*************************************************************************/
DistributionAgent::~DistributionAgent() throw(){
	IAS_TRACER;
}
/*************************************************************************/
IO::ProducerOutput* DistributionAgent::createProducer(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext){

	IAS_TRACER;

	dmProducerOutput->setDestination(getAttribute(dmContext,strAttribute));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Destination: "<<dmProducerOutput->getDestination());

	return IAS_DFT_FACTORY<IO::ProducerOutput>::Create(dmProducerOutput,pWorkContextManager);
}
/*************************************************************************/
void DistributionAgent::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 	DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DistributionAgent starts:");

	IAS_DFT_FACTORY<IO::ProducerOutput>::PtrHolder ptrOutput(createProducer(dmContext));

	ptrOutput->send(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DistributionAgent ends");

}
/*************************************************************************/
void DistributionAgent::computeRaw(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
								   API::Message* pMessage){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DistributionAgent starts:");

	IAS_DFT_FACTORY<IO::ProducerOutput>::PtrHolder ptrOutput(createProducer(dmContext));

	ptrOutput->send(dmContext,*pMessage->getContent());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DistributionAgent ends");

}
/*************************************************************************/
}
}
}
}
}
