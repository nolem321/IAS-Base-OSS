/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCProcess.cpp
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
#include "commonlib/sys/proc/Executor.h"

#include "TCProcess.h"

#include<stdlib.h>
#include <unistd.h>

using namespace ::IAS::SYS::Proc;
namespace IAS {
namespace TCT {

/*************************************************************************/
TCProcess::TCProcess(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCProcess::~TCProcess() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void TCProcess::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("test1",&::IAS::TCT::TCProcess::test1);
	theTestRunner.addCase("test2",&::IAS::TCT::TCProcess::test2);
	theTestRunner.addCase("test3",&::IAS::TCT::TCProcess::test3);
	TestUnit::init("TCProcess",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCProcess::test1() {
	IAS_TRACER;

	MyWorker  aWorker(5);
	IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<Process>::Create(&aWorker));

	ptrProcess->start();
	std::cerr << "P: Started: "<<ptrProcess->getPid()<< "\n";
	std::cerr << "P: Is run(const String& strCaseName)ning: "<<ptrProcess->isRunning()<< "\n";
	ptrProcess->wait();
	std::cerr << "P: Stopped: "<<ptrProcess->getPid()<< "\n";
}
/*************************************************************************/
void TCProcess::test2() {
	IAS_TRACER;

	MyWorker  aWorker(10);
	IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<Process>::Create(&aWorker));

	ptrProcess->start();
	std::cerr << "P: Started: "<<ptrProcess->getPid()<< "\n";
	std::cerr << "P: Is run(const String& strCaseName)ning: "<<ptrProcess->isRunning()<< "\n";
	sleep(3);
	std::cerr << "P: terminating: "<<std::endl;
	ptrProcess->stop();
	std::cerr << "P: Is run(const String& strCaseName)ning: "<<ptrProcess->isRunning()<< "\n";
	ptrProcess->wait();
	std::cerr << "P: Stopped: "<<ptrProcess->getPid()<< "\n";
}
/*************************************************************************/
void TCProcess::test3() {
	IAS_TRACER;

	IAS_DFT_FACTORY<Executor>::PtrHolder ptrExecutor(IAS_DFT_FACTORY<Executor>::Create("/bin/sed"));

	ptrExecutor->appendArg("s/root/ROOT/g");
	//ptrExecutor->appendArg("/etc/passwd");

	IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<Process>::Create(ptrExecutor.getPointer()));
	//ptrProcess->setOutputStream("/tmp/process.out");
	ptrProcess->setInputStream("/etc/passwd");

	ptrProcess->start();
	std::cerr << "P: Started: "<<ptrProcess->getPid()<< "\n";
	ptrProcess->wait();
	std::cerr << "P: Stopped: "<<ptrProcess->getPid()<< "\n";
}
/*************************************************************************/

TCProcess::MyWorker::MyWorker(int iStart) {
	IAS_TRACER;
	this->iStart = iStart;
}
/*************************************************************************/

void TCProcess::MyWorker::run() {
	IAS_TRACER;
	std::cerr << "I:" << iStart << "," << ((unsigned int) getpid()) << "\n";
	iterate( iStart);
	std::cerr << "I: Finished. \n";
}

/*************************************************************************/
void TCProcess::MyWorker::iterate(int i) {
	IAS_TRACER;

	while (i > 0) {
		sleep(1);
		std::cerr<<"count down:"<<i<<std::endl;
		i--;
	}

}
/*************************************************************************/

}
}
