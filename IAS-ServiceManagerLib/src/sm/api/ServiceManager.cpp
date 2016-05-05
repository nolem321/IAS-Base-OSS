/*
 * File: IAS-ServiceManagerLib/src/sm/api/ServiceManager.cpp
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
#include "ServiceManager.h"

#include <commonlib/commonlib.h>

#include "sm/worker/Iterator.h"
#include "sm/worker/WorkerForStart.h"
#include "sm/worker/WorkerForStop.h"
#include "sm/worker/WorkerForTxtDsp.h"
#include "sm/worker/WorkerForDMDsp.h"
#include "sm/worker/WorkerForSupervisor.h"

#include "sm/mon/Monitor.h"
#include "sm/mon/ServiceStatus.h"
#include "sm/cfg/dataobjects.h"
#include <unistd.h>

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace API {

/*************************************************************************/
ServiceManager::ServiceManager(){
	IAS_TRACER;
	ptrConfig = IAS_DFT_FACTORY<Cfg::Config>::Create(EnvTools::GetEnv("IAS_SM_CFGDIR"));
}
/*************************************************************************/
ServiceManager::~ServiceManager() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void ServiceManager::startServices(const Cfg::GrpAttrPairList& lstGrpAttrPair) {
	IAS_TRACER;

	Cfg::ServiceIdxList lstSelectedServices;

	ptrConfig->getServiceIdxListByGrpAttrs(lstGrpAttrPair, lstSelectedServices);

	IAS_DFT_FACTORY<Worker::WorkerForStart>::PtrHolder ptrWorker(IAS_DFT_FACTORY<Worker::WorkerForStart>::Create(ptrConfig.getPointer()));
	IAS_DFT_FACTORY<Worker::Iterator>::PtrHolder ptrIterator(Worker::Iterator::Create(ptrConfig, ptrWorker, lstSelectedServices));

	ptrIterator->execute();
}
/*************************************************************************/
void ServiceManager::stopServices(const Cfg::GrpAttrPairList& lstGrpAttrPair,  bool bAsync) {
	IAS_TRACER;

	Cfg::ServiceIdxList lstSelectedServices;

	ptrConfig->getServiceIdxListByGrpAttrs(lstGrpAttrPair, lstSelectedServices);

	IAS_DFT_FACTORY<Worker::WorkerForStop>::PtrHolder ptrWorker(Worker::WorkerForStop::Create(ptrConfig, bAsync));
	IAS_DFT_FACTORY<Worker::Iterator>::PtrHolder ptrIterator(Worker::Iterator::Create(ptrConfig, ptrWorker, lstSelectedServices));

	ptrIterator->execute();
}
/*************************************************************************/
void ServiceManager::printServicesStatus(const Cfg::GrpAttrPairList& lstGrpAttrPair) {
	IAS_TRACER;

	Cfg::ServiceIdxList lstSelectedServices;
	ptrConfig->getServiceIdxListByGrpAttrs(lstGrpAttrPair, lstSelectedServices);

	IAS_DFT_FACTORY<Mon::Monitor>::PtrHolder ptrMonitor(IAS_DFT_FACTORY<Mon::Monitor>::Create(ptrConfig.getPointer()));
	ptrMonitor->refresh();

	IAS_DFT_FACTORY<Worker::WorkerForTxtDsp>::PtrHolder ptrWorker(
			IAS_DFT_FACTORY<Worker::WorkerForTxtDsp>::Create(ptrConfig.getPointer(), ptrMonitor.getPointer()));

	IAS_DFT_FACTORY<Worker::Iterator>::PtrHolder ptrIterator(Worker::Iterator::Create(ptrConfig, ptrWorker, lstSelectedServices));

	ptrIterator->execute();

}
/*************************************************************************/
void ServiceManager::prepareServicesStatus(const ::org::invenireaude::sm::api::Ext::GrpAttrPairList& lstGrpAttrPair,
		   	   	   	   	   	   	   	   	   ::org::invenireaude::sm::api::Ext::ServiceStatusList& lstServiceStatus){
	IAS_TRACER;

	Cfg::ServiceIdxList lstSelectedServices;

	Cfg::GrpAttrPairList lstGrpAttrPairTmp;

	fillGrpAttrPairList(lstGrpAttrPair,lstGrpAttrPairTmp);

	ptrConfig->getServiceIdxListByGrpAttrs(lstGrpAttrPairTmp, lstSelectedServices);

	IAS_DFT_FACTORY<Mon::Monitor>::PtrHolder ptrMonitor(IAS_DFT_FACTORY<Mon::Monitor>::Create(ptrConfig.getPointer()));
	ptrMonitor->refresh();

	IAS_DFT_FACTORY<Worker::WorkerForDMDsp>::PtrHolder ptrWorker(
				IAS_DFT_FACTORY<Worker::WorkerForDMDsp>::Create<const Cfg::Config*,
																const Mon::Monitor*,
																::org::invenireaude::sm::api::Ext::ServiceStatusList&>(
																		ptrConfig.getPointer(),
																		ptrMonitor.getPointer(),
																		lstServiceStatus));

	IAS_DFT_FACTORY<Worker::Iterator>::PtrHolder ptrIterator(Worker::Iterator::Create(ptrConfig, ptrWorker, lstSelectedServices));

	ptrIterator->execute();
}
/*************************************************************************/
void ServiceManager::watchServices(const Cfg::GrpAttrPairList& lstGrpAttrPair){
	IAS_TRACER;

	Cfg::ServiceIdxList lstSelectedServices;

	ptrConfig->getServiceIdxListByGrpAttrs(lstGrpAttrPair, lstSelectedServices);

	IAS_DFT_FACTORY<Mon::Monitor>::PtrHolder ptrMonitor;
	IAS_DFT_FACTORY<Worker::WorkerForSupervisor>::PtrHolder ptrWorker;
	IAS_DFT_FACTORY<Worker::Iterator>::PtrHolder ptrIterator;

	while(true){

		IAS_LOG(LogLevel::INSTANCE.isInfo(), "Looping ...");

		if(ptrConfig->refresh() || ptrMonitor.isNull()){
			IAS_LOG(LogLevel::INSTANCE.isInfo(), "Refreshing...");
			ptrMonitor = IAS_DFT_FACTORY<Mon::Monitor>::Create(ptrConfig.getPointer());
			ptrWorker = IAS_DFT_FACTORY<Worker::WorkerForSupervisor>::Create(ptrConfig.getPointer(), ptrMonitor.getPointer());
			ptrIterator = Worker::Iterator::Create(ptrConfig, ptrWorker, lstSelectedServices);
		}


		ptrMonitor->refresh();
		ptrIterator->execute();
		usleep(ptrConfig->getRefeshMS()*1000);
	}

}
/*************************************************************************/
void ServiceManager::fillGrpAttrPairList(const ::org::invenireaude::sm::api::Ext::GrpAttrPairList& lstInputGrpAttrPair,
						 Cfg::GrpAttrPairList& lstOutputGrpAttrPair){
	IAS_TRACER;

	lstOutputGrpAttrPair.clear();

	for(int iIdx=0; iIdx<lstInputGrpAttrPair.size(); iIdx++){

		const org::invenireaude::sm::api::GrpAttrPair* dmPair=lstInputGrpAttrPair.at(iIdx);
		lstOutputGrpAttrPair.push_back(Cfg::GrpAttrPair(dmPair->getName(),dmPair->getValue()));
	}
}
/*************************************************************************/
const Cfg::Config* ServiceManager::getConfig() const {
	IAS_TRACER;
	return ptrConfig;
}
/*************************************************************************/
}
}
}
