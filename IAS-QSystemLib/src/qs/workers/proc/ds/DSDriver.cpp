/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/DSDriver.cpp
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
#include "DSDriver.h"
#include<qs/log/LogLevel.h>
#include <qs/workers/proc/wcm/WorkContextManager.h>
#include <qs/workers/proc/GlobalContext.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

#include "wrapper/Wrapper.h"

using namespace org::invenireaude::qsystem::workers;
namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {

/*************************************************************************/
DSDriver::WrapperHolder::~WrapperHolder(){
	IAS_TRACER;

	if(getPointer()->isReusable())
		pass();

}
/*************************************************************************/
DSDriver::DSDriver(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter,
		 	 	   WCM::WorkContextManager* pWorkContextManager):
		pSession(0){
	IAS_TRACER;

	pSession = pWorkContextManager->ds.lookupSession(uriConnectionKey,dmParameter);
	pDataFactory=pWorkContextManager->getGlobalContext()->getDataFactory();

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Driver: "<<uriConnectionKey.getURIString());
}
/*************************************************************************/
DSDriver::~DSDriver() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Wrapper::Wrapper* DSDriver::getStatement(const String& strSpecification, ::IAS::DM::DataObject* dm){
	IAS_TRACER;


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()||true,"Lookup: "<<(String)strSpecification);

	if(hmWrappers.count(strSpecification))
		return hmWrappers[strSpecification];

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()||true,"not found, I will create a new one ");


	IAS_DFT_FACTORY< Wrapper::Wrapper >::PtrHolder ptrWrapper(Wrapper::Wrapper::Create(pSession,strSpecification,pDataFactory,dm));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()||true,"Reusable: "<<ptrWrapper->isReusable());

	if(ptrWrapper->isReusable()){
		return hmWrappers[strSpecification]=ptrWrapper.pass();
	}


	return ptrWrapper.pass();
}
/*************************************************************************/
const DM::DataFactory* DSDriver::getDataFactory(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pDataFactory);
	return pDataFactory;
}
/*************************************************************************/
::IAS::DS::API::Session*  DSDriver::getSession(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pSession);
	return pSession;
}
/*************************************************************************/
}
}
}
}
}
