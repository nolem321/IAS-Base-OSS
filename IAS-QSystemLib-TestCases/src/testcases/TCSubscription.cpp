/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCSubscription.cpp
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

#include "TCSubscription.h"
#include <qs/api.h>

#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#include <qs/Impl/shm/Administrator.h>


namespace IAS{
using namespace QS::API;

namespace TCT{

/*************************************************************************/
const String TCSubscription::C_Subscription("T.TCSubscription");
/*************************************************************************/
TCSubscription::TCSubscription(TestSuite* pTestSuite):
	theTestRunner(this),
	bStop(false),
	iNumMsgs(5){
	IAS_TRACER;
	init(pTestSuite);

}

URI TCSubscription::uri("shm://sample");

/*************************************************************************/

TCSubscription::~TCSubscription() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCSubscription::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCSubscription::caseOne);
	TestUnit::init("TCSubscription",&theTestRunner,pTestSuite);
}
/*************************************************************************/
int iPid;
void TCSubscription::Distributor::run(){
	IAS_TRACER;

	switch(iPid=fork()){

		case 0:
			//std::cerr<<"************* NEW PROCESS ***************: "<<getpid()<<std::endl;
			//LogLevel::INSTANCE.bIsTrace=true;
			IAS_LOG(LogLevel::INSTANCE.bIsInfo,"New welcomes: "<<getpid())
			Environment::GetInstance()->shutdown();
			QS::SHM::Administrator::StartDistributor("sample");
			exit(0);
			break;
		case -1:
			IAS_THROW(SystemException("Distributor fork."));
			break;
		default:

			IAS_LOG(LogLevel::INSTANCE.bIsInfo,"New process: "<<iPid)

	//	while(!pMyTest->isStopping()){
	//		sleep(1);
	//	}

		//IAS_LOG(LogLevel::INSTANCE.bIsInfo,"Killing distributor: "<<iPid);
		//kill(iPid,SIGINT);
		//sleep(5);
		//kill(iPid,SIGKILL);
		//waitpid(iPid,NULL,0);
	}

}
/*************************************************************************/
void TCSubscription::Publisher::run(){
	IAS_TRACER;
	sleep(2);
	Environment* TheEnvironment = Environment::GetInstance();
	Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
	Session::PtrHolder ptrSession(ptrConnection->createSession(Session::SM_NonTransacted));

	Destination dest(C_Subscription);
	IAS::QS::API::Publisher::PtrHolder ptrPublisher(ptrSession->createPublisher(dest));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

	int iNumMsgs=pMyTest->getNumMsgs();


	for (int i = 0; i < iNumMsgs; i++) {
			ptrNewMessage = ptrConnection->createMessage();

			(*ptrNewMessage->getContent())<<2000+i;
			ptrPublisher->publish(ptrNewMessage);
			usleep((unsigned int)rand()%1000000);
		}

}
/*************************************************************************/
void TCSubscription::Subscriber::run(){
	IAS_TRACER;

	sleep(1);

	IAS_LOG(LogLevel::INSTANCE.bIsInfo,"  *** Subscriber !!!");

	Environment* TheEnvironment = Environment::GetInstance();
	Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
	Session::PtrHolder ptrSession(ptrConnection->createSession(Session::SM_NonTransacted));

	Destination dest(C_Subscription);
	IAS::QS::API::Subscriber::PtrHolder ptrSubscriber(ptrSession->createSubscriber(dest));

	IAS_DFT_FACTORY<Message>::PtrHolder ptrNewMessage;

	int iNumMsgs=pMyTest->getNumMsgs();

	for (int i = 0; i < iNumMsgs; i++) {
			ptrNewMessage = ptrSubscriber->receive(5000);
			long iValue;
			(*(ptrNewMessage->getContent()))>>iValue;

			IAS_LOG(LogLevel::INSTANCE.isInfo(),iValue<<" ? "<<(2000+i));
			if(iValue != 2000+i)
				IAS_LOG(LogLevel::INSTANCE.bIsError,"Wrong value: "<<(void*)this<<", "
						<<iValue<<" ? "<<(2000+i));

		}

}
/*************************************************************************/
void TCSubscription::caseOne(){

	{
	//	IAS_DFT_FACTORY<Administration>::PtrHolder ptrAdm(IAS_DFT_FACTORY<Administration>::Create("sample"));

		try{
			//ptrAdm->createTopic(C_Subscription);
		}catch(::IAS::Exception& e){
			IAS_LOG(LogLevel::INSTANCE.bIsError,e.toString());
		}

	}
	
	Environment* TheEnvironment = Environment::GetInstance();
	TheEnvironment->shutdown();

	Distributor distributor;
	Publisher   publish(this);
	Subscriber  subscriber1(this);
	Subscriber  subscriber2(this);


	distributor.run();
	publish.start();
	subscriber1.start();
	subscriber2.start();

	publish.join();
	subscriber1.join();
	subscriber2.join();

	sleep(5);

	TheEnvironment->shutdown();

	{
		QS::SHM::Administrator::DisplaySystem("sample",std::cerr);
		TheEnvironment->shutdown();
	//IAS_DFT_FACTORY<Administration>::PtrHolder ptrAdm(IAS_DFT_FACTORY<Administration>::Create("sample"));

	try{
		//ptrAdm->deleteTopic(C_Subscription);
		}catch(::IAS::Exception& e){
			IAS_LOG(LogLevel::INSTANCE.bIsError,e.toString());
		}
	}

	bStop=true;
	int iStatus;
	kill(iPid,SIGINT);
	waitpid(iPid,&iStatus,0);
	if(WIFSIGNALED(iStatus))
		IAS_LOG(LogLevel::INSTANCE.bIsError,"signal="<<WTERMSIG(iStatus));

	//distributor.join();

    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
