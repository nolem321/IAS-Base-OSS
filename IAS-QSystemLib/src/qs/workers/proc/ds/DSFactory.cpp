/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ds/DSFactory.cpp
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
#include "DSFactory.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include <commonlib/sys/ModuleFactoryStore.h>

#include "DSManager.h"
#include "DSDriver.h"

#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>
#include <org/invenireaude/qsystem/workers/Connection.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace DS {
/*************************************************************************/
static String _HackURI(const String& strSpecs) {

	//TODO this is old ?

	/*
	 * Some convenient hacks:
	 *   "file:abc" => "file://${PWD}/abc"
	 *   "file:/abc" => "file:///abc"
	 *   "file:stdout" => "file:///stdout"
	 *   etc...
	 */


	String strNewSpec(strSpecs);

	if (strSpecs.find("://") == String::npos) {

		if (strSpecs.find(":/") == String::npos) {

			if (strSpecs.compare("sqlite:stdout") == 0) {
				strNewSpec = "sqlite://localhost/stdout";
			} else if (strSpecs.compare("file:stdin") == 0) {
				strNewSpec = "sqlite://localhost/stdin";
			} else {

				String strNew("://localhost");
				strNew += EnvTools::GetEnv("PWD");
				strNew += "/";
				size_t iPos = strSpecs.find(':');
				strNewSpec.replace(iPos, 1, strNew);
			}

		} else {

			String strNew("://localhost/");
			size_t iPos = strSpecs.find(':');
			strNewSpec.replace(iPos, 1, strNew);

		}

	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(), "Url ["<<strNewSpec<<"]");

	return strNewSpec;

}
/*************************************************************************/
DSFactory::DSFactory(const ::org::invenireaude::qsystem::workers::ds::Specification* dmSpecification,
					 DSManager* pDSManager,
					 WCM::WorkContextManager* pWorkContextManager):
		pDSManager(pDSManager),
		pWorkContextManager(pWorkContextManager){
	IAS_TRACER;

	if(!dmSpecification)
		return;

	const ds::Ext::ParameterList& lstDataSources(dmSpecification->getDatasourcesList());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"DataSources: "<<lstDataSources.size());

	for(int iIdx=0;iIdx<lstDataSources.size();iIdx++){
		if(hmDataSources.count(lstDataSources.at(iIdx)->getName()))
			IAS_THROW(BadUsageException("Duplicated datasource: ")<<lstDataSources.at(iIdx)->getName());
		hmDataSources[lstDataSources.at(iIdx)->getName()]=lstDataSources.at(iIdx);
	}
}
/*************************************************************************/
DSFactory::~DSFactory()throw(){}
/*************************************************************************/
void DSFactory::createDataSource(const String& strName)const{

	IAS_TRACER;

	if(!hmDataSources.count(strName))
		IAS_THROW(ItemNotFoundException("Data source not found: ")<<strName);

	const ds::Parameter* ptrParameter=hmDataSources.at(strName);

	if(ds::DataFactory::GetInstance()->getParameterType()->equals(ptrParameter->getType())){
		pDSManager->addDSDriver(ptrParameter->getName(),
				IAS_DFT_FACTORY<DS::DSDriver>::Create(
						ds::DataFactory::GetInstance()->getParameterType()->cast(ptrParameter),
						pWorkContextManager));
	}else{
		IAS_THROW(InternalException(ptrParameter->getType()->getName()+"Unknown specification type."));
	}


}
/*************************************************************************/
::org::invenireaude::qsystem::workers::ds::Ext::SpecificationPtr
 DSFactory::DataSourceSpecsToDM(const String& strSpecs){

	IAS_TRACER;

	ds::Ext::SpecificationPtr ptrResult;

	if(strSpecs.find(':') == String::npos){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strSpecs);

		DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strSpecs,
														ds::DataFactory::GetInstance()->getContaingDataFactory(),
														ds::DataFactory::GetInstance()->getSpecificationType()));

		ptrResult = ds::DataFactory::GetInstance()->getSpecificationType()->cast(dm);

	}else{

		URI uri(_HackURI(strSpecs));

		ds::Ext::ParameterPtr ptrParameter;
		ptrParameter=ds::DataFactory::GetInstance()->getParameterType()->createParameter();

		ptrParameter->createConnection()->setProtocol(uri.getProtocol());
		ptrParameter->getConnection()->setHost(/*url.getDomain()*/ uri.getHost());
		ptrParameter->getConnection()->setLocation(/*url.getDomain()*/ uri.getPath());
		//ptrParameter->setDestination(url.getPath());
		//ptrParameter->setTransacted(false);
		ptrParameter->setName("db");

		try{
			String strDBName=uri.getValue("name");
			ptrParameter->setName(strDBName);
		}catch(...){}

		ptrResult=ds::DataFactory::GetInstance()->getSpecificationType()->createSpecification();
		ptrResult->setDatasources(ptrParameter);
	}

	return ptrResult;
}
/*************************************************************************/
IAS::DS::API::Session::TransactionMode DSFactory::StringToTransactionMode(const String& strMode){

	//TODO add uppercase to String

	String strValue;
	for(String::const_iterator it=strMode.begin();it != strMode.end();it++)
		strValue+=(char)toupper(*it);

	if(!strValue.compare("TXN"))
		return IAS::DS::API::Session::SM_Transacted;

	if(!strValue.compare("NONTXN"))
		return IAS::DS::API::Session::SM_NonTransacted;

	if(!strValue.compare("XA"))
		return IAS::DS::API::Session::SM_XAManaged;

	IAS_THROW(BadUsageException(String("Unknown session mode:")+strMode));
}
/*************************************************************************/
}
}
}
}
}

