/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/EventCounterFactory.cpp
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
#include "EventCounterFactory.h"
#include <qs/log/LogLevel.h>


#include <org/invenireaude/qsystem/workers/ec/EventCounter.h>
#include <org/invenireaude/qsystem/workers/ec/SimpleEventCounter.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>


#include "EventCounterStore.h"
#include "../GlobalContext.h"

#include "simple/EventCounter.h"

#include <qs/workers/proc/wcm/Registry.h>

using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {
/*************************************************************************/
static String _HackURI(const String& strSpecs) {
	//TODO some hacking for eventCounter url ?
	return strSpecs;
}
/*************************************************************************/
void EventCounterFactory::CreateEventCounters(const ::org::invenireaude::qsystem::workers::ec::Specification* dmSpecification,
					   	 EventCounterStore *pEventCounterStore,
						 GlobalContext *pGlobalContext){
	IAS_TRACER;

	const ec::Ext::EventCounterList& lstEventCounters(dmSpecification->getEcsList());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"ECs: "<<lstEventCounters.size());

	for(int iIdx=0;iIdx<lstEventCounters.size();iIdx++){

		ec::Ext::EventCounterPtr dmEventCounter(lstEventCounters.at(iIdx)->duplicateEventCounter());

		if((!dmEventCounter->getConnection()->isSetProtocol() &&
				dmEventCounter->getConnection()->isSetAlias())
				||dmEventCounter->getConnection()->getProtocol().compare("registry") == 0){

			dmEventCounter->setConnection(WCM::Registry::GetInstance()->ecs.lookup(dmEventCounter->getConnection()->getAlias())->duplicateConnection());
		}


		if(ec::DataFactory::GetInstance()->getSimpleEventCounterType()->equals(dmEventCounter->getType())){

			pEventCounterStore->addEventCounter(dmEventCounter->getName(),
					IAS_DFT_FACTORY<Simple::EventCounter>::Create(
							ec::DataFactory::GetInstance()->getSimpleEventCounterType()->cast(dmEventCounter)));

		}else{
			IAS_THROW(InternalException(dmEventCounter->getType()->getName()+"Unknown specification type."));
		}

	}

}
/*************************************************************************/

::org::invenireaude::qsystem::workers::ec::Ext::SpecificationPtr
 EventCounterFactory::ECSpecsToDM(const String& strSpecs){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::ec::Ext::SpecificationPtr ptrResult;

	if(!strSpecs.empty() && strSpecs.find(':') == String::npos){

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strSpecs);

			DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strSpecs,
																ec::DataFactory::GetInstance()->getContaingDataFactory(),
																ec::DataFactory::GetInstance()->getSpecificationType()));

			ptrResult = ec::DataFactory::GetInstance()->getSpecificationType()->cast(dm);

		}else{

			URI uri(_HackURI(strSpecs));

			if(uri.getProtocol().compare("sec") == 0){
				ec::Ext::SimpleEventCounterPtr ptrEventCounter(ec::DataFactory::GetInstance()->getSimpleEventCounterType()->createSimpleEventCounter());
				ptrEventCounter->setName("default");
				ptrResult->setEcs(ptrEventCounter);
			}else {
				IAS_THROW(BadUsageException(uri.getProtocol()+" bad protocol name for eventCounter."));
			}
	}

	return ptrResult;
}
/*************************************************************************/
}
}
}
}
}
