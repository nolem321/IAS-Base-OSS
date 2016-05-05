/*
 * File: IAS-ServiceManagerLib/src/sm/worker/IteratorForSelected.cpp
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
#include "IteratorForSelected.h"

#include <commonlib/commonlib.h>
#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
IteratorForSelected::IteratorForSelected(const Cfg::ServiceIdxList& lstServiceIdx, const Cfg::Config *pConfig, IWorker* pWorker)
	:	lstServiceIdx(lstServiceIdx){
	IAS_TRACER;
	Iterator::init(pConfig, pWorker);
}

/*************************************************************************/
IteratorForSelected::~IteratorForSelected() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void IteratorForSelected::executeImpl(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute starts");

	for(Cfg::ServiceIdxList::const_iterator it = lstServiceIdx.begin();
		it != lstServiceIdx.end();
		it++){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execute for service name: "<<(pConfig->getService(*it))->getName());
		executeServiceAction(pConfig->getService(*it));
	}
}
/*************************************************************************/
}
}
}
