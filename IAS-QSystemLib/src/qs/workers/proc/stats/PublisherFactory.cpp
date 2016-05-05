/*
 * File: PublisherFactory.cpp
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

#include "PublisherFactory.h"

#include <org/invenireaude/qsystem/workers/stats/DataFactory.h>
#include <org/invenireaude/qsystem/workers/stats/Console.h>
#include <org/invenireaude/qsystem/workers/stats/Sender.h>

#include "pub/Console.h"
#include "pub/Sender.h"

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

/*************************************************************************/
PublisherFactory::PublisherFactory(){
	IAS_TRACER;
}

/*************************************************************************/
PublisherFactory::~PublisherFactory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
stats::Ext::SpecificationPtr PublisherFactory::SpecsToDM(const String& strSpecs){
	IAS_TRACER;

	stats::Ext::SpecificationPtr dmResult(stats::DataFactory::GetInstance()->getSpecificationType()->createSpecification());

	if(strSpecs.compare("console") == 0){

		dmResult->getPublishersList().add(stats::DataFactory::GetInstance()->getConsoleType()->createConsole());

	}else{

		stats::Ext::SenderPtr dmSender(stats::DataFactory::GetInstance()->getSenderType()->createSender());
		dmSender->setOutput(strSpecs);

	}

	return dmResult;
}
/*************************************************************************/
Publisher* PublisherFactory::CreatePublisher(const ::org::invenireaude::qsystem::workers::stats::Publisher* dmPublisher){
	IAS_TRACER;

	IAS_DFT_FACTORY<Publisher>::PtrHolder ptrResult;

	const DM::Type *pType = dmPublisher->getType();

	if(stats::DataFactory::GetInstance()->getConsoleType()->equals(pType)){
		ptrResult = IAS_DFT_FACTORY<Pub::Console>::Create();
	}else if(stats::DataFactory::GetInstance()->getSenderType()->equals(pType)){
		ptrResult = IAS_DFT_FACTORY<Pub::Sender>::Create(
				stats::DataFactory::GetInstance()->getSenderType()->cast(dmPublisher));
	}else{
		IAS_THROW(BadUsageException("Unknown publisher type!"));
	}

	return ptrResult.pass();
}
/*************************************************************************/

}
}
}
}
}
