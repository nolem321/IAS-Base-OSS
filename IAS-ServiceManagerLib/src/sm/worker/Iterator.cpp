/*
 * File: IAS-ServiceManagerLib/src/sm/worker/Iterator.cpp
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
#include "Iterator.h"

#include <commonlib/commonlib.h>

#include "IteratorForAll.h"
#include "IteratorForSelected.h"

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "IWorker.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
Iterator::Iterator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Iterator::~Iterator() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Iterator::execute(){
	IAS_TRACER;
	executeImpl();
}
/*************************************************************************/
void Iterator::executeServiceAction(const ::org::invenireaude::sm::cfg::Service *pService){
	IAS_TRACER;
	pWorker->work(pService);
	return;
}
/*************************************************************************/
void Iterator::init(const Cfg::Config *pConfig, IWorker* pWorker){
	IAS_TRACER;
	this->pConfig=pConfig;
	this->pWorker=pWorker;
}
/*************************************************************************/
Iterator* Iterator::Create(const Cfg::Config *pConfig,
						   IWorker* pWorker,
						   const Cfg::ServiceIdxList& lstServiceIdx){
	IAS_TRACER;


	//TODO empty condition yields in all services !!

	if(lstServiceIdx.size() == 0){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Iterator for all.");
		return IAS_DFT_FACTORY<IteratorForAll>::Create(pConfig,pWorker);
	}else{
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Iterator for selected:"<<lstServiceIdx.size());
		return IAS_DFT_FACTORY<IteratorForSelected>::Create(lstServiceIdx,pConfig,pWorker);
	}

}
/*************************************************************************/
}
}
}
