/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/DataObjects.cpp
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
#include "commonlib/commonlib.h"

#include "DataObjects.h"
#include <qs/api.h>

#include <qs/workers/proc/io/IOFactory.h>
#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <dm/tools/Formatter.h>
#include <dm/datamodel.h>

namespace IAS{
using namespace QS::API;
using namespace QS::Workers::Proc;

namespace TCT{


/*************************************************************************/
DataObjects::DataObjects(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

	StringList lstXSDFiles;
	IAS::EnvTools::GetEnvTokenized("IAS_LANG_XSD",lstXSDFiles);

	IAS_DFT_FACTORY<DM::XML::XSDHelper>::PtrHolder ptrXSDHelper(
				IAS_DFT_FACTORY<DM::XML::XSDHelper>::Create(org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContaingDataFactory()));

	for(StringList::const_iterator it = lstXSDFiles.begin();
		it != lstXSDFiles.end();
		it++)
			ptrXSDHelper->defineTypesFromFile(*it);

	ptrFmtFactory=IAS_DFT_FACTORY<QS::Fmt::FmtFactory>::Create(
			org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContaingDataFactory());


	pOriginalAllocator=DM::Impl::MemoryManager::GetAllocatorForData();

	ptrMemoryManager=IAS_DFT_FACTORY<RegionMemoryManager>::Create(pOriginalAllocator,6000000);
	DM::Impl::MemoryManager::GetInstance()->setAllocatorForData(ptrMemoryManager);

}
/*************************************************************************/

DataObjects::~DataObjects() throw(){
	IAS_TRACER;
	DM::Impl::MemoryManager::GetInstance()->setAllocatorForData(pOriginalAllocator);
}
/*************************************************************************/
void DataObjects::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::DataObjects::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::DataObjects::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::DataObjects::caseThree);
	TestUnit::init("DataObjects",&theTestRunner,pTestSuite);
}

void inspect(DM::DataObject* dm){

	const DM::Type* pType=dm->getType();

	if(pType->isDataObjectType()){

		const DM::PropertyList& lstProperties(pType->asComplexType()->getProperties());

		for(int iIdx = 0; iIdx < lstProperties.getSize(); ++iIdx) {
			const DM::Property* pProperty= lstProperties.getProperty(iIdx);
			const String& strProperty(pProperty->getName());

			if(pProperty->isMulti()){
				DM::DataObjectList& lstChild(dm->getList(strProperty));
				for(int i=0;i<lstChild.size();i++)
					inspect(lstChild.at(i));
			}else if(dm->isSet(strProperty))
					inspect(dm->getDataObject(strProperty));
		}

	}
}
/*************************************************************************/
void inspectIdx(DM::DataObject* dm){

	const DM::Type* pType=dm->getType();

	if(pType->isDataObjectType()){

		const DM::PropertyList& lstProperties(pType->asComplexType()->getProperties());

		for(int iIdx = 0; iIdx < lstProperties.getSize(); ++iIdx) {
			const DM::Property* pProperty= lstProperties.getProperty(iIdx);

			if(pProperty->isMulti()){
				DM::DataObjectList& lstChild(dm->getList(pProperty));
				for(int i=0;i<lstChild.size();i++)
					inspectIdx(lstChild.at(i));
			}else if(dm->isSet(pProperty))
					inspectIdx(dm->getDataObject(pProperty));
		}

	}
}
/*************************************************************************/
void DataObjects::action(const String& strFile, int iIterations){

	IAS_TRACER;

	QS::Fmt::Formatter* pFormater(ptrFmtFactory->getFormatter("XML"));

	String strContent;

	InputFile::LoadString(strFile,strContent);

	TimeSample ts(true);

	for(int i = 0; i < iIterations; i++) {

		DM::DataObjectPtr dmData;
		QS::API::Attributes attr;

		StringStream ssContent(strContent);
		pFormater->read(dmData,ssContent,&attr);

		DM::DataObjectPtr dmData2(dmData->duplicate());

		if(!ptrMemoryManager.isNull())
			ptrMemoryManager->freeAll();

	}

	long iTime = ts.getSample() / 1000 + 1;

	std::cout << strFile<<", parsed " <<iIterations<<" times, size: "<<strContent.length()<<", time: "<< iTime << "ms., avg: "
		<< iIterations * 1000 / iTime << " m/s."<<std::endl;

}

/*************************************************************************/
void DataObjects::caseOne(){

	action("samples/perftest/data/customer.xml",100);
}
/*************************************************************************/
void DataObjects::caseTwo(){

}
/*************************************************************************/
void DataObjects::caseThree(){

}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
