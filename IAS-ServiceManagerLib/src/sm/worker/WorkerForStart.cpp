/*
 * File: IAS-ServiceManagerLib/src/sm/worker/WorkerForStart.cpp
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
#include "WorkerForStart.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "exe/Handler.h"
#include "StartStopHelper.h"

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
WorkerForStart::WorkerForStart(const ::IAS::SM::Cfg::Config *pConfig) {
	IAS_TRACER;
	this->pConfig = pConfig;
	ptrStartStopHelper = IAS_DFT_FACTORY<StartStopHelper>::Create(pConfig);
}
/*************************************************************************/
WorkerForStart::~WorkerForStart() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void WorkerForStart::work(const ::org::invenireaude::sm::cfg::Service* pService) {
	IAS_TRACER;

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);
	int iCount = dmResourceGrp->getCount();

	for (int iIdx = 0; iIdx < iCount; iIdx++) {
		ptrStartStopHelper->startInstance(pService, iIdx);
	}/* FOR: instances */
}
/*************************************************************************/

}
}
}
