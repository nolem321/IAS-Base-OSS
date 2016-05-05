/*
 * File: IAS-QSystemLib/src/qs/workers/proc/mode/ProcessorWorker.cpp
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
#include "ProcessorWorker.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "../io/IOManager.h"
#include "../io/Input.h"
#include "../io/Output.h"

#include "../ds/DSDriver.h"
#include "../ds/DSFactory.h"

#include "../txm/TXMDriver.h"
#include "../txm/TXMFactory.h"

#include "../logic/Logic.h"

#include <climits>

#include "dm/Impl/DataFactory.h"
#include <dm/Impl/MemoryManager.h>

#include <org/invenireaude/qsystem/workers/Context.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>

#include "../GlobalContext.h"
#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "../io/IOFactory.h"

#include <qs/Impl/Environment.h>

#include "../exception/RollbackMeException.h"

#include <qs/workers/proc/stats/LogicStatsStore.h>
#include <qs/workers/proc/stats/LogicStats.h>

#include <qs/ui/Messages.h>


using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Mode {

/*************************************************************************/
ProcessorWorker::ProcessorWorker(GlobalContext *pGlobalContext,
	   	   	   	   	   	   	   int iLogicIdx):
	   	   	   	   	   	       pLogicStats(0),
							   iCommitCount(1),
							   strName("noName"){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pGlobalContext);
	this->pGlobalContext=pGlobalContext;

	ptrWorkContext=IAS_DFT_FACTORY<WCM::WorkContextManager>::Create(pGlobalContext);
	pWorkContextShared=ptrWorkContext;

 	const ::org::invenireaude::qsystem::workers::spec::Specification* dmSpecification=pGlobalContext->getSpecification();

 	const logic::Logic* dmLogic = dmSpecification->getLogicSpec()->getLogicsList().at(iLogicIdx);

 	try{
 		Stats::LogicStatsStore* pLogicStatsStore = pGlobalContext->getLogicStatsStore();

 		if(dmLogic->isSetName())
 			strName=dmLogic->getName();
 		else
 			strName=TypeTools::IntToString(iLogicIdx)+":"+dmLogic->getType()->getName();

 		pLogicStats=pLogicStatsStore->createLogicStats(strName);

 	}catch(ItemNotFoundException&){}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Create Logic ** ");

	ptrLogic=pGlobalContext->getLogicFactory()->createLogic(dmLogic,ptrWorkContext);

	if(dmLogic->isSetCommitCount())
		iCommitCount=dmLogic->getCommitCount();

	if(iCommitCount < 1 || iCommitCount > 1000)
		IAS_THROW(BadUsageException("Bad commit count value, the acceptable range is: 1-1000"));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** memory  ** ");

	pOriginalAllocator=DM::Impl::MemoryManager::GetAllocatorForData();

	try{
		EnvTools::GetEnv("IAS_REGION");
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** New allocator  ** ");
		//TODO Parameterize this IAS_REGION allocator.
		ptrMemoryManager=IAS_DFT_FACTORY<RegionMemoryManager>::Create(pOriginalAllocator,6000000);
		DM::Impl::MemoryManager::GetInstance()->setAllocatorForData(ptrMemoryManager);
	}catch(...){};


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** S E T U P   finishes  ** ");


}
/*************************************************************************/
ProcessorWorker::~ProcessorWorker() throw(){
	IAS_TRACER;

	//TODO thread races here ?
	DM::Impl::MemoryManager::GetInstance()->setAllocatorForData(pOriginalAllocator);

	if(!ptrWorkContext.isNull())
		try{
			ptrWorkContext->rollback();
		}catch(Exception& e){
		}
}
/*************************************************************************/
void ProcessorWorker::iterate(){
	IAS_TRACER;

	bool bStop(false);

	while(pGlobalContext->allDone() &&
		  !SYS::Signal::GetInstance()->isStopping() &&
		  !bStop){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Iteration: ");

		bool bCommitOnEndOfData = false;

		try{

			//MemoryManager::GetInstance()->clearNewFlag();

			ptrWorkContext->begin();

			for(int iCount = 0; iCount < iCommitCount; iCount++){

				if(!ptrMemoryManager.isNull())
					ptrMemoryManager->freeAll();

				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Receiving ... ["<<iCount+1<<" of "<<iCommitCount<<"]");
				ptrLogic->receive(iCount > 0);

				TimeSample ts(pLogicStats != NULL);
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Computing ...");
				ptrLogic->compute();

				if(pLogicStats)
					pLogicStats->addSuccess(ts);

				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Done :"<<ts.getSample());

			}

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Committing !");
			ptrWorkContext->commit();

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Done !");

			//MemoryManager::GetInstance()->printToStream(std::cerr,true);

		}catch(EndOfDataException& e){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** End of data !");
			ptrWorkContext->commit();
			bStop=true;
		}catch(RollbackMeException& e ){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Exception:"<<e.toString());
			UserMessage(UI::Messages::MSGE_Rollback)<<e.getName()<<e.getInfo();
			ptrWorkContext->rollback();
			bStop=false;
		}catch(Exception& e ){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Exception:"<<e.toString());
			throw;
		}catch(std::exception& e){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Exception:"<<e.what());
			IAS_THROW(Exception(e.what()));
#ifdef __GNUC__
		}catch(__cxxabiv1::__forced_unwind&){
		throw;
#endif
		}catch(...){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Unknown exception !!!");
			bStop=true;
		}
	}

}
/*************************************************************************/
}
}
}
}
}
