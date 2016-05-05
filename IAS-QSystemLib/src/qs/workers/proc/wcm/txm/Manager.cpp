/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/txm/Manager.cpp
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
#include "../../wcm/txm/Manager.h"

#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <qs/workers/proc/txm/TXMDriver.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>

using namespace ::org::invenireaude::qsystem::workers;

#include "Context.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace TXM {

/*************************************************************************/
Manager::Manager(WorkContextManager *pWorkContextManager):pWorkContextManager(pWorkContextManager){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pWorkContextManager);

	const spec::Specification* dmSpecification=pWorkContextManager->getGlobalContext()->getSpecification();

	if(dmSpecification->isSetTxmSpec()){

		ptrFactory=IAS_DFT_FACTORY<Proc::TXM::TXMFactory>::Create(dmSpecification->getTxmSpec(),
																  this,
															      pWorkContextManager);

		//TODO (M) XA names to activate ?
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** XA is being activated.  ** ");

		const txm::Ext::ParameterList& lstParameters(dmSpecification->getTxmSpec()->getTransactionManagersList());

		for(int iIdx=0; iIdx<lstParameters.size(); iIdx++)
			getTXMDriver(lstParameters.at(iIdx)->getName())->getSession();
	}

}
/*************************************************************************/
Manager::~Manager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Proc::TXM::TXMDriver* Manager::getTXMDriver(const String& strName)const{
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"txm["<<strName<<"]")

	if(!ptrFactory)
		IAS_THROW(ItemNotFoundException("No data sources are available !"));

	if(!hmTXMDrivers.hasKey(strName))
		ptrFactory->createTransactionManager(strName);

	return const_cast<Proc::TXM::TXMDriver*>(hmTXMDrivers.at(strName));

}
/*************************************************************************/
void Manager::addTXMDriver(const String& strName, Proc::TXM::TXMDriver *pTXMDriver){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pTXMDriver);

	if(hmTXMDrivers.hasKey(strName))
		IAS_THROW(InternalException(strName+" already exists on TXM lists."));

	hmTXMDrivers[strName]=pTXMDriver;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"hmTXMDrivers["<<strName<<"]="<<(void*)pTXMDriver);
}
/*************************************************************************/
}
}
}
}
}
}

