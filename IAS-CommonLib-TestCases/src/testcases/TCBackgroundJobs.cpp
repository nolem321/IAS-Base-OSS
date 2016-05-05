/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBackgroundJobs.cpp
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
#include <commonlib/commonlib.h>
#include "TCBackgroundJobs.h"

#include<stdlib.h>
#include <unistd.h>

namespace IAS {
namespace TCT {

TCBackgroundJobs::TCBackgroundJobs(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}

TCBackgroundJobs::~TCBackgroundJobs() throw (){
	IAS_TRACER;
}

/*************************************************************************/
void TCBackgroundJobs::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCBackgroundJobs::caseALL);
	::IAS::TestUnit::init("TCBackgroundJobs",&theTestRunner, pTestSuite);
}
/*************************************************************************/
void TCBackgroundJobs::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<BackgroundJobsExecutor>::PtrHolder ptrExecutor(IAS_DFT_FACTORY<BackgroundJobsExecutor>::Create(1));

	ptrExecutor->setCompleteJobsOnDelete(true);

	for(int i=0; i<100; i++){
		IAS_DFT_FACTORY<SimpleBJ>::PtrHolder ptrNewJob;
		ptrNewJob = IAS_DFT_FACTORY<SimpleBJ>::Create(i);
		ptrExecutor->enqueue(ptrNewJob.pass());
	}


	sleep(10);
}

/*************************************************************************/

void TCBackgroundJobs::SimpleBJ::onStart(){
	IAS_TRACER;

	std::cerr<<id<<":started\n";
	for(int i=0; i<10000; i++){
		//std::cerr<<id<<":"<<i<<"\n";

		for(int j=0; j<1000; j++){
			int a=1.0*234/2.34/j/i*10.0;
		}
	}
	std::cerr<<id<<":ended\n";
}

/*************************************************************************/
void TCBackgroundJobs::SimpleBJ::onError(::IAS::Exception& e){};

/*************************************************************************/
void TCBackgroundJobs::SimpleBJ::onCancel(){};
/*************************************************************************/
TCBackgroundJobs::SimpleBJ::SimpleBJ(int id){this->id = id;};
/*************************************************************************/

}
}
