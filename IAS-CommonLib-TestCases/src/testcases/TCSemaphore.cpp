/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSemaphore.cpp
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
#include "TCSemaphore.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <unistd.h>

namespace IAS {
namespace TCT {
using namespace IPC;

TCSemaphore::TCSemaphore(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}

TCSemaphore::~TCSemaphore() throw () {
	IAS_TRACER;
}

void TCSemaphore::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCSemaphore::caseALL);
	TestUnit::init("TCSemaphore",&theTestRunner,pTestSuite);
}

void TCSemaphore::caseALL() {
	IAS_TRACER;

	String strKeyPath("/tmp");

	try{
		SemaphoreArray::Descriptor aSemaphoreDesc(SemaphoreArray::Descriptor::M_CLEANER);
		aSemaphoreDesc.setKeyByToken(strKeyPath, 1);
		SemaphoreArray sem(aSemaphoreDesc);
	}catch(...){};
	try{
		SharedMemory::Descriptor aSharedMemoryeDesc(SemaphoreArray::Descriptor::M_CLEANER);
		aSharedMemoryeDesc.setKeyByToken(strKeyPath, 2);
		aSharedMemoryeDesc.setSize(64);
		SharedMemory shm(aSharedMemoryeDesc);
	}catch(...){};

	SemaphoreArray::Descriptor aSemaphoreDesc(SemaphoreArray::Descriptor::M_OWNER);
	aSemaphoreDesc.setKeyByToken(strKeyPath, 1);
	SemaphoreArray semArray(aSemaphoreDesc);

	SemaphoreArray::Semaphore semOne=semArray[0];
	semOne.reset();
	semArray.resetAll();
	semOne.inc();

	SharedMemory::Descriptor aSharedMemoryeDesc(SemaphoreArray::Descriptor::M_OWNER);
	aSharedMemoryeDesc.setKeyByToken(strKeyPath, 2);
	aSharedMemoryeDesc.setSize(64);
	SharedMemory shm(aSharedMemoryeDesc);

	*((int*) shm.getAddress()) = 0;

	int iNumThreads = 3;
	Worker worker;
	worker.init(strKeyPath);

	IAS_DFT_FACTORY<Thread>::PtrHoldersCollection phcThread;


	for (int i = 0; i < iNumThreads; i++) {

		IAS_DFT_FACTORY<Thread>::PtrHolder ptrThread(IAS_DFT_FACTORY<Thread>::Create(&worker));
		ptrThread->start();
		phcThread.addPointer(ptrThread.pass());
	}

	{
	//	SemaphoreDescriptor desc(SemaphoreDescriptor::M_CLEANER);
	//	desc.setKeyByToken(strKeyPath, 1);
	//	Semaphore sem(desc);
	//	sleep(1);
	}

	std::cerr<<"Deleted !\n";

	for(IAS_DFT_FACTORY<Thread>::PtrHoldersCollection::iterator it=phcThread.begin();
				it != phcThread.end(); it++){

		(*it)->join();
	}

}

/*************************************************************************/
TCSemaphore::Worker::Worker():
	aSemaphoreDesc(ResourceDescriptor::M_USER), aSharedMemoryDesc(ResourceDescriptor::M_USER) {
}
/*************************************************************************/
void TCSemaphore::Worker::init(const String& strPath){
	IAS_TRACER;

	aSemaphoreDesc.setKeyByToken(strPath, 1);
	aSharedMemoryDesc.setKeyByToken(strPath, 2);
}
/*************************************************************************/
void TCSemaphore::Worker::run() {
	IAS_TRACER;


	std::cerr << "\nSTARTED:" << ((unsigned int) pthread_self()) <<std::endl;
	runImpl();
	return;

	int child;
	switch(child=fork()){

	case -1: perror("fork"); break;
	case 0: runImpl(); break;

	default:
		waitpid(child,NULL,0);
		std::cerr << "\nCHILD Terminated:" <<child<<std::endl;
	}

}
/*************************************************************************/
void TCSemaphore::Worker::runImpl() {
	IAS_TRACER;

	SemaphoreArray semArray(aSemaphoreDesc);
	SemaphoreArray::Semaphore sem=semArray[0];
	SharedMemory shm(aSharedMemoryDesc);

	volatile int *pData = (int*) shm.getAddress();

	std::cerr << "\nACCESS:" << ((unsigned int) pthread_self()) << "=" << shm.getSize() << " at " << shm.getAddress() << std::endl;

	usleep(rand() % 1000000);

	while ((*pData) < 15) {

		std::cerr << "\nDATA:" << ((unsigned int) pthread_self()) << "=" << *pData << std::endl;
		{
			SYS::Locker locker(&sem);
			usleep(rand() % 1000000);

			(*pData)++;

			if((rand() % 10) > 8 ){
						std::cerr << "\nTERMINATE myself :" << ((unsigned int) pthread_self()) << "=" << *pData << std::endl;
						pthread_cancel(pthread_self());
						//exit(0);

			}

		}
		usleep(rand() % 1000000);

	}

	out:
	std::cerr << "\nEND:" << ((unsigned int) pthread_self()) << "=" << *pData << std::endl;
}
/*************************************************************************/
}
}
