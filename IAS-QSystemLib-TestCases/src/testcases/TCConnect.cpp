/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCConnect.cpp
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

#include "TCConnect.h"
#include <qs/api.h>

namespace IAS{
using namespace QS::API;

namespace TCT{


/*************************************************************************/
TCConnect::TCConnect(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCConnect::~TCConnect() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCConnect::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCConnect::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::TCConnect::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::TCConnect::caseThree);
	TestUnit::init("TCConnect",&theTestRunner,pTestSuite);
}


/*************************************************************************/
void TCConnect::caseOne(){
	

	Environment* TheEnvironment = Environment::GetInstance();

	URI uri;

	uri.setProtocol("shm");
	uri.setHost("sample");

	Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
	TheEnvironment->shutdown();

    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
void TCConnect::caseTwo(){

	{

		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();

		URI uri;
		uri.setProtocol("shm");
		uri.setHost("sample");

		Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
		Session::PtrHolder ptrSession(ptrConnection->createSession(Session::SM_NonTransacted));

		Destination destination("Q.DEFAULT");
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
void TCConnect::caseThree(){

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
