/*
 * File: IAS-QSystemExe/src/parameters/CreateParameters.cpp
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
#include "CreateParameters.h"

#include <commonlib/commonlib.h>
#include <qs/api/Administrator.h>
#include <org/invenireaude/qsystem/DataFactory.h>

#include <org/invenireaude/qsystem/MemorySettings.h>
#include <org/invenireaude/qsystem/MemorySize.h>
#include <org/invenireaude/qsystem/QueueSettings.h>
#include <org/invenireaude/qsystem/SessionSettings.h>
#include <org/invenireaude/qsystem/ContentSettings.h>

#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ds/DataFactory.h>
#include <org/invenireaude/qsystem/workers/cache/DataFactory.h>
#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>
#include <org/invenireaude/qsystem/workers/txm/DataFactory.h>
#include <org/invenireaude/qsystem/workers/logic/DataFactory.h>

#include <lang/model/Model.h>

using namespace ::org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace Parameters {

/*************************************************************************/
CreateParameters::CreateParameters(int argc, char* argv[]){
	IAS_TRACER;

	    Lang::Model::Model::RegisterBuildInTypes();

		org::invenireaude::qsystem::workers::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::io::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::ds::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::txm::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::cache::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::ec::DataFactory::GetInstance();
		org::invenireaude::qsystem::workers::logic::DataFactory::GetInstance();

	try{

		ptrXMLHelper = IAS_DFT_FACTORY<DM::XML::XMLHelper>::Create(org::invenireaude::qsystem::workers::DataFactory::GetInstance()->getContaingDataFactory());

	}catch(Exception& e){
		//IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
		throw;
	}

	::IAS::QS::Parameters::ProgramParameters::init(argc,argv,"c:n:m:");

}
/*************************************************************************/
CreateParameters::~CreateParameters() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CreateParameters::printCmdDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
void CreateParameters::printArgsDesc(std::ostream& os) const{
	IAS_TRACER;
}
/*************************************************************************/
Ext::SystemPtr CreateParameters::getSystemDescription(){
	IAS_TRACER;

	if(dmSystem.isNull()){

		if(hmIndicators['c']){
			loadXML(hmValues['c']);
		}else{

			dmSystem=DataFactory::GetInstance()->createSystem();

			if(!hmIndicators['n'])
				IAS_THROW(BadUsageException("You must specify -n option when creating default system."));

			int iMaxQueues = 32;

			if(hmIndicators['m'])
				iMaxQueues=TypeTools::StringToInt(hmValues['m']);

			dmSystem->setName(hmValues['n']);
			dmSystem->createQueues();

			dmSystem->getQueues()->setMaxQueues(iMaxQueues);
			dmSystem->getQueues()->setDftSize(100);

			dmSystem->createContent();
			dmSystem->getContent()->setMaxEntries(iMaxQueues*200);

			dmSystem->createSessions();
			dmSystem->getSessions()->setMaxSessions(32);


			dmSystem->createMemory();
			dmSystem->getMemory()->createHeap();
			dmSystem->getMemory()->createQueue();
			dmSystem->getMemory()->createData();

			dmSystem->getMemory()->getHeap()->setValue(0x40000+0x1000*iMaxQueues);
			dmSystem->getMemory()->getQueue()->setValue(0x40000+0x4000*iMaxQueues);
			dmSystem->getMemory()->getData()->setValue(0x40000+0x10000*iMaxQueues);
		}
	}

	return dmSystem;
}
/*************************************************************************/
void CreateParameters::loadXML(const String& strFileName){
	IAS_TRACER;
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"XML from:"<<strFileName);

	IAS_DFT_FACTORY<DM::XML::XMLDocument>::PtrHolder ptrDoc(ptrXMLHelper->readFile(strFileName));
	dmSystem = DataFactory::GetInstance()->getSystemType()->cast(ptrDoc->getRootObject());


}
/*************************************************************************/
}
}
}
