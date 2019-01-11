/*
 * File: IAS-QSystemLib/src/qs/workers/proc/txm/TXMFactory.cpp
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
#include "TXMFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <commonlib/sys/ModuleFactoryStore.h>

#include "TXMManager.h"
#include "TXMDriver.h"

#include <org/invenireaude/qsystem/workers/txm/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace TXM {
/*************************************************************************/
static String _HackURI(const String& strSpecs) {
	//TODO some hacking for txm url ?
	return strSpecs;
}
/*************************************************************************/
TXMFactory::~TXMFactory()throw(){};
/*************************************************************************/
TXMFactory::TXMFactory(const ::org::invenireaude::qsystem::workers::txm::Specification* dmSpecification,
					 TXMManager* pTXMManager):
		pTXMManager(pTXMManager){
	IAS_TRACER;

	if(!dmSpecification)
		return;

	const txm::Ext::ParameterList& lstTXManagers(dmSpecification->getTransactionManagersList());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"TXMs: "<<lstTXManagers.size());

	for(int iIdx=0;iIdx<lstTXManagers.size();iIdx++){
		if(hmTXManagers.count(lstTXManagers.at(iIdx)->getName()))
			IAS_THROW(BadUsageException("Duplicated TX Manager: ")<<lstTXManagers.at(iIdx)->getName());
		hmTXManagers[lstTXManagers.at(iIdx)->getName()]=lstTXManagers.at(iIdx);
	}
}
/*************************************************************************/
void TXMFactory::createTransactionManager(const String& strName)const{

	IAS_TRACER;

	if(!hmTXManagers.count(strName))
			IAS_THROW(ItemNotFoundException("TX Manager not found: ")<<strName);

	const txm::Parameter* ptrParameter=hmTXManagers.at(strName);


	if(txm::DataFactory::GetInstance()->getParameterType()->equals(ptrParameter->getType())){
		pTXMManager->addTXMDriver(ptrParameter->getName(),
				IAS_DFT_FACTORY<TXM::TXMDriver>::Create(
						txm::DataFactory::GetInstance()->getParameterType()->cast(ptrParameter),
						pWorkContextManager));
	}else{
		IAS_THROW(InternalException(ptrParameter->getType()->getName()+"Unknown specification type."));
	}

}
/*************************************************************************/
::org::invenireaude::qsystem::workers::txm::Ext::SpecificationPtr
 TXMFactory::TransactionManagerSpecsToDM(const String& strSpecs){

	IAS_TRACER;

	txm::Ext::SpecificationPtr ptrResult;

	if(strSpecs.find(':') == String::npos){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strSpecs);

		DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strSpecs,
														txm::DataFactory::GetInstance()->getContaingDataFactory(),
														txm::DataFactory::GetInstance()->getSpecificationType()));

		ptrResult = txm::DataFactory::GetInstance()->getSpecificationType()->cast(dm);

	}else{

		URI uri(_HackURI(strSpecs));

		txm::Ext::ParameterPtr ptrParameter;
		ptrParameter=txm::DataFactory::GetInstance()->getParameterType()->createParameter();

		ptrParameter->createConnection()->setProtocol(uri.getProtocol());
		ptrParameter->getConnection()->setHost(/*url.getDomain()*/ uri.getHost());
		ptrParameter->getConnection()->setLocation(/*url.getDomain()*/ uri.getPath());
		//ptrParameter->setDestination(url.getPath());
		//ptrParameter->setTransacted(false);
		ptrParameter->setName("txm");

		ptrResult=txm::DataFactory::GetInstance()->getSpecificationType()->createSpecification();
		ptrResult->setTransactionManagers(ptrParameter);
	}

	return ptrResult;
}
/*************************************************************************/
}
}
}
}
}

