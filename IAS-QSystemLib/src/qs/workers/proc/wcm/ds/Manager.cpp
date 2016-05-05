/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/ds/Manager.cpp
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
#include "../../wcm/ds/Manager.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/ds/DSDriver.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

#include "Context.h"

#include <org/invenireaude/qsystem/workers/spec/Specification.h>
#include <org/invenireaude/qsystem/workers/ds/Specification.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace DS {

/*************************************************************************/
Manager::Manager(WorkContextManager *pWorkContextManager):pWorkContextManager(pWorkContextManager){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pWorkContextManager);

	const spec::Specification* dmSpecification=pWorkContextManager->getGlobalContext()->getSpecification();

	if(dmSpecification->isSetDatasourceSpec())
		ptrFactory=IAS_DFT_FACTORY<Proc::DS::DSFactory>::Create(dmSpecification->getDatasourceSpec(),
																this,
																pWorkContextManager);

}
/*************************************************************************/
Manager::~Manager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Proc::DS::DSDriver* Manager::getDSDriver(const String& strName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"db["<<strName<<"]")

	if(!ptrFactory)
		IAS_THROW(ItemNotFoundException("No data sources are available !"));

	if(!hmDSDrivers.hasKey(strName))
		ptrFactory->createDataSource(strName);

	return const_cast<Proc::DS::DSDriver*>(hmDSDrivers.at(strName));

}
/*************************************************************************/
void Manager::addDSDriver(const String& strName, Proc::DS::DSDriver *pDSDriver){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDSDriver);

	if(hmDSDrivers.hasKey(strName))
		IAS_THROW(InternalException(strName+" already exists on db lists."));

	hmDSDrivers[strName]=pDSDriver;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"hmDSDrivers["<<strName<<"]="<<(void*)pDSDriver);
}
/*************************************************************************/
}
}
}
}
}
}
