/*
 * File: PublisherStore.cpp
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

#include "PublisherStore.h"
#include "Publisher.h"

#include "PublisherFactory.h"
#include "LogicStatsStore.h"

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

#include <org/invenireaude/qsystem/workers/stats/Specification.h>

#include <unistd.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Stats {

/*************************************************************************/
PublisherStore::PublisherStore(const stats::Specification* dmSpecification,
							GlobalContext* pGlobalContext):
		Thread(this),
		pGlobalContext(pGlobalContext),
		iRefresh(1){
	IAS_TRACER;

	const stats::Ext::PublisherList& lstPublishers(dmSpecification->getPublishersList());

	for(int iIdx=0;iIdx<lstPublishers.size();iIdx++){
		const stats::Publisher * dmPublisher = lstPublishers.at(iIdx);

		phcPublishers.addPointer(PublisherFactory::CreatePublisher(dmPublisher));
	}

	if(dmSpecification->isSetRefresh())
		iRefresh=dmSpecification->getRefresh();

	ptrLogicStatsStore = IAS_DFT_FACTORY<LogicStatsStore>::Create();
}
/*************************************************************************/
PublisherStore::~PublisherStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
LogicStatsStore* PublisherStore::getLogicStatsStore(){
	IAS_TRACER;
	return ptrLogicStatsStore;
}
/*************************************************************************/
void PublisherStore::run(){
	IAS_TRACER;

	IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::WCM::WorkContextManager >::PtrHolder
		ptrWorkContextManager(IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::WCM::WorkContextManager >::Create(pGlobalContext));

	while(pGlobalContext->allDone() &&
			!SYS::Signal::GetInstance()->isStopping()) {

		sleep(iRefresh);

		try {

			stats::Ext::LogicSamplesSetPtr dmLogicSamplesSet(ptrLogicStatsStore->getSamples(true));

			for(IAS_DFT_FACTORY<Publisher>::PtrHoldersCollection::iterator it=phcPublishers.begin();
					it != phcPublishers.end(); it++) {

				(*it)->publish(dmLogicSamplesSet, ptrWorkContextManager);
			}

			ptrWorkContextManager->commit();

		} catch(Exception* e) {
			ptrWorkContextManager->rollback();
		}
	}

}
/*************************************************************************/

}
}
}
}
}
