/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Get.cpp
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

#include "Get.h"
#include <qs/api.h>

#include <qs/workers/proc/io/IOFactory.h>
#include <org/invenireaude/qsystem/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>
#include <dm/tools/Formatter.h>

#include <qs/Impl/shm/Administrator.h>

namespace IAS{
using namespace QS::API;
using namespace QS::Workers::Proc;

namespace TCT{


/*************************************************************************/
Get::Get(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

	dmConnection=org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createConnection();

	URI uri("shm://QS.Perf.Test");

	IO::IOFactory::UpdateConnection(uri,dmConnection);

	org::invenireaude::qsystem::Ext::SystemPtr dmSystem(
			org::invenireaude::qsystem::DataFactory::GetInstance()->getSystemType()->cast(
			DM::Tools::Formatter::LoadFile("samples/perftest/system.qs.xml",
			org::invenireaude::qsystem::DataFactory::GetInstance()->getContaingDataFactory())));

	QS::SHM::Administrator::CreateSystem(dmSystem);
}

/*************************************************************************/

Get::~Get() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void Get::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::Get::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::Get::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::Get::caseThree);
	TestUnit::init("Get",&theTestRunner,pTestSuite);
}


/*************************************************************************/
void Get::caseOne(){
	

	Environment* TheEnvironment = Environment::GetInstance();

	URI uri;

	TheEnvironment->shutdown();

    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
void Get::caseTwo(){

	{

		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();


		Connection::PtrHolder ptrConnection(TheEnvironment->connect(dmConnection));
		Session::PtrHolder ptrSession(ptrConnection->createSession(Session::SM_NonTransacted));

		Destination destination("Q.BIG");
		Producer::PtrHolder ptrProducer(
				ptrSession->createProducer(destination));
		Consumer::PtrHolder ptrConsumer(
				ptrSession->createConsumer(destination));

		IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

		for (int i = 0; i < 7; i++) {

			ptrNewMessage = ptrConnection->createMessage();
			Content* pContent=ptrNewMessage->getContent();
			(*pContent)<<(1000000+i);
			ptrNewMessage->getAttributes()->setValue("ATTR1","VAL1");
			ptrNewMessage->getAttributes()->setValue("ATTR2","VAL23456789");
			ptrNewMessage->getAttributes()->setValue("ATTRTEST",TypeTools::IntToString(i));
			ptrProducer->produce(ptrNewMessage);
		}

		for (int i = 0; i < 7; i++) {
			ptrNewMessage = ptrConsumer->receive();
			Content* pContent=ptrNewMessage->getContent();
			long iValue;
			(*pContent)>>iValue;
			std::cerr <<"TESTTEST:       "<< i << " : " << iValue << ", a="
					<< (void*) (ptrNewMessage.operator ->()) <<
					"TESTATTR="<<ptrNewMessage->getAttributes()->getValue("ATTRTEST")<<std::endl;

		}


	}
    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
void Get::caseThree(){

	{
		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();

	}
    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
