/*
 * File: IAS-QSystemLib/src/qs/workers/proc/logic/DaemonExecute.cpp
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
#include "DaemonExecute.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/io/Output.h>
#include <qs/workers/proc/io/IOManager.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../GlobalContext.h"
#include "../ProgramProvider.h"

#include <org/invenireaude/qsystem/workers/DaemonControl.h>
#include <org/invenireaude/qsystem/workers/logic/ExeName.h>

#include <unistd.h>

using namespace ::org::invenireaude::qsystem::workers;
using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {

/*************************************************************************/
DaemonExecute::DaemonExecute(const ::org::invenireaude::qsystem::workers::logic::DaemonExecute* dmParameters,
					 	 	 WCM::WorkContextManager* pWorkContextManager):
	Execute(dmParameters, pWorkContextManager),
	iWakupIntervalMS(1000),
	iBatchSize(1){
	IAS_TRACER;

	const workers::logic::Ext::ExeNameList& lstExeNames(dmParameters->getLoadList());

	for(int iIdx=0;iIdx< lstExeNames.size();iIdx++){
		pWorkContextManager->getGlobalContext()->getProgramProvider()->load(lstExeNames.at(iIdx),ptrProgramSet);
	}

	if(dmParameters->isSetWakeUpInterval())
		iWakupIntervalMS=dmParameters->getWakeUpInterval();

	iNextInterval=iWakupIntervalMS;

	if(dmParameters->isSetBatchSize())
		iBatchSize=dmParameters->getBatchSize();

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Default WakeUpInterval: "<<iWakupIntervalMS<<", next: "<<iNextInterval);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"BatchSize:              "<<iBatchSize);

	if(!isDM())
		IAS_LOG(QS::LogLevel::INSTANCE.isError(),"Parsing switch is ignored for the Daemon Execute Logic.");
}
/*************************************************************************/
DaemonExecute::~DaemonExecute() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void DaemonExecute::receive(bool bNoWait){
	IAS_TRACER;

	if(!bNoWait){
		IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Sleeping:"<<iNextInterval);
		Thread::Cancellation ca(true);
		usleep(1000*(iNextInterval));
	}
}
/*************************************************************************/
void DaemonExecute::compute(){
	IAS_TRACER;

	workers::Ext::DaemonControlPtr dmDaemonControl;
	dmDaemonControl = workers::DataFactory::GetInstance()->getDaemonControlType()->createDaemonControl();

	dmDaemonControl->setActive(true);
	dmDaemonControl->setDefaultInterval(iWakupIntervalMS);
	dmDaemonControl->setNextInterval(iWakupIntervalMS);
	dmDaemonControl->setBatchSize(iBatchSize);

	TimeSample tsStart(true);

	workers::Ext::ContextPtr dmContext;
	dmContext = workers::DataFactory::GetInstance()->getContextType()->createContext();

	DM::DataObjectPtr dmValue(dmDaemonControl);
	computeDM(dmContext, dmValue);

	if(dmDaemonControl->isSetActive() && !dmDaemonControl->getActive())
		IAS_THROW(EndOfDataException());

	iNextInterval = dmDaemonControl->getNextInterval();
	long iElapsed = tsStart.getSample()/1000;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Sleeping: "<<(iNextInterval-iElapsed)<<"Elapsed: "<<iElapsed<<", next: "<<iNextInterval);

	if(iNextInterval > iElapsed)
		iNextInterval = iNextInterval - iElapsed;
	else
		iNextInterval = 0;

}
/*************************************************************************/
void DaemonExecute::computeDM(::org::invenireaude::qsystem::workers::Ext::ContextPtr& dmContext,
					 		  DM::DataObjectPtr& dmData){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DaemonExecute starts.");

	ptrProgramSet->execute(dmContext,dmData);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"==DaemonExecute ends.");
}
/*************************************************************************/
}
}
}
}
}
