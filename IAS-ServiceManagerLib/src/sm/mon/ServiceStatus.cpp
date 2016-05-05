/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ServiceStatus.cpp
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
#include "ServiceStatus.h"

#include <commonlib/commonlib.h>

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
ServiceStatus::ServiceStatus(const ::org::invenireaude::sm::cfg::Service* pService, int iCount) {
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pService);
	this->pService = pService;
	tabInstancesStatus.resize(iCount);
}
/*************************************************************************/
ServiceStatus::~ServiceStatus() throw () {
	IAS_TRACER;
}
/*************************************************************************/
const ::org::invenireaude::sm::cfg::Service* ServiceStatus::getService() const {
	IAS_TRACER;
	return pService;
}
/*************************************************************************/
const ServiceStatus::InstanceStatus* ServiceStatus::getInstanceStatus(unsigned int iIdx) const {
	IAS_TRACER;
	if (iIdx < 0 || iIdx >= tabInstancesStatus.size())
		IAS_THROW(BadUsageException("iIdx<0 || iIdx>=tabInstancesStatus.size()"));

	return &tabInstancesStatus.at(iIdx);
}
/*************************************************************************/
ServiceStatus::InstanceStatus* ServiceStatus::getInstanceStatus(unsigned int iIdx) {
	IAS_TRACER;
	return const_cast<ServiceStatus::InstanceStatus*> (static_cast<const ServiceStatus*> (this)->getInstanceStatus(iIdx));
}
/*************************************************************************/
}
}
}
