/*
 * File: IAS-ServiceManagerLib/src/sm/worker/IteratorForAll.cpp
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
#include "IteratorForAll.h"
#include <commonlib/commonlib.h>
#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
IteratorForAll::IteratorForAll(const Cfg::Config *pConfig, IWorker* pWorker){
	IAS_TRACER;
	Iterator::init(pConfig, pWorker);
}
/*************************************************************************/
IteratorForAll::~IteratorForAll() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IteratorForAll::executeImpl(){
	IAS_TRACER;
	const Ext::ServiceList& lstServicesList(pConfig->getServicesList());

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute for all: "<<lstServicesList.size());

	for(int iIdx=0; iIdx<lstServicesList.size(); iIdx++){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute for idx: "<<iIdx<<", "<<lstServicesList.at(iIdx)->getName());
		executeServiceAction(lstServicesList.at(iIdx));
	}
}
/*************************************************************************/
}
}
}
