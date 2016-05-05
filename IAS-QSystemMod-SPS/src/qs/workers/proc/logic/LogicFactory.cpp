/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/LogicFactory.cpp
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
#include <dm/datamodel.h>

#include "SPSActionExecute.h"
#include "SPSStartExecute.h"
#include "SPSCleaner.h"
#include "SPSScheduler.h"

#include<qs/log/sps/LogLevel.h>

#include <qs/workers/proc/logic/LogicFactory.h>
#include <org/invenireaude/qsystem/workers/sps/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/External.h>

#include "sps/ProcessCache.h"

using namespace IAS;
using namespace ::IAS::QS::Workers::Proc::Logic;
using namespace ::org::invenireaude::qsystem::workers::sps;

/*************************************************************************/
extern "C"{

static IAS::Mutex _ias_qs_lf_sps_mutex;

/*************************************************************************/
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_lf_spsaction(const ::org::invenireaude::qsystem::workers::logic::Logic*    dmLogic,
											              ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){
	IAS_TRACER;

	Mutex::Locker locker(_ias_qs_lf_sps_mutex);
	SPS::ProcessCache::GetInstance();

	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::SPSActionExecute>::Create(
			DataFactory::GetInstance()->getSPSActionExecuteType()->cast(dmLogic),
				pWorkContextManager);
}
/*************************************************************************/
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_lf_spsstart(const ::org::invenireaude::qsystem::workers::logic::Logic*    dmLogic,
											              ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){
	IAS_TRACER;

	Mutex::Locker locker(_ias_qs_lf_sps_mutex);
	SPS::ProcessCache::GetInstance();


	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::SPSStartExecute>::Create(
			DataFactory::GetInstance()->getSPSStartExecuteType()->cast(dmLogic),
				pWorkContextManager);
}
/*************************************************************************/
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_lf_spsscheduler(const ::org::invenireaude::qsystem::workers::logic::Logic*    dmLogic,
											              ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){
	IAS_TRACER;
	Mutex::Locker locker(_ias_qs_lf_sps_mutex);
	SPS::ProcessCache::GetInstance();

	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::SPSScheduler>::Create(
			DataFactory::GetInstance()->getSPSSchedulerType()->cast(dmLogic),
				pWorkContextManager);
}
/*************************************************************************/
::IAS::QS::Workers::Proc::Logic::Logic* _ias_qs_lf_spscleaner(const ::org::invenireaude::qsystem::workers::logic::Logic*    dmLogic,
											              ::IAS::QS::Workers::Proc::WCM::WorkContextManager* pWorkContextManager){
	IAS_TRACER;

	Mutex::Locker locker(_ias_qs_lf_sps_mutex);
	SPS::ProcessCache::GetInstance();

	return IAS_DFT_FACTORY< ::IAS::QS::Workers::Proc::Logic::SPSCleaner>::Create(
			DataFactory::GetInstance()->getSPSCleanerType()->cast(dmLogic),
				pWorkContextManager);
}
/*************************************************************************/
void _ias_qs_lf_sps(LogicFactory* pLogicFactory){

	IAS_TRACER;

	Mutex::Locker locker(_ias_qs_lf_sps_mutex);

	pLogicFactory->registerExternalFactory(DataFactory::GetInstance()->getSPSActionExecuteType(), _ias_qs_lf_spsaction);
	pLogicFactory->registerExternalFactory(DataFactory::GetInstance()->getSPSStartExecuteType(),  _ias_qs_lf_spsstart);
	pLogicFactory->registerExternalFactory(DataFactory::GetInstance()->getSPSSchedulerType(),     _ias_qs_lf_spsscheduler);
	pLogicFactory->registerExternalFactory(DataFactory::GetInstance()->getSPSCleanerType(),       _ias_qs_lf_spscleaner);

}
/*************************************************************************/
}
