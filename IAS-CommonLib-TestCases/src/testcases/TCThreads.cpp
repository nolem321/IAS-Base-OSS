/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCThreads.cpp
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
#include "TCThreads.h"

#include<stdlib.h>

namespace IAS {
namespace TCT {


/*************************************************************************/
TCThreads::TCThreads(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/
TCThreads::~TCThreads() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCThreads::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCThreads::caseALL);
	TestUnit::init("TCThreads",&theTestRunner,pTestSuite);
}
/*************************************************************************/

void TCThreads::caseALL() {
	IAS_TRACER;

	MyThread mt1(30);
	MyThread mt2(50);


	IAS_DFT_FACTORY<Thread>::PtrHolder ptrThread1(IAS_DFT_FACTORY<Thread>::Create(&mt1));
	IAS_DFT_FACTORY<Thread>::PtrHolder ptrThread2(IAS_DFT_FACTORY<Thread>::Create(&mt2));

	ptrThread1->start();
	ptrThread2->start();

	ptrThread1->join();
	ptrThread2->join();
}
/*************************************************************************/

TCThreads::MyThread::MyThread(int iStart) {
	IAS_TRACER;
	this->iStart=iStart;
}

/*************************************************************************/
void TCThreads::MyThread::run() {
	IAS_TRACER;
	try{
		ptrObject=IAS_DFT_FACTORY<TCThreads::Object>::Create();

		iterate(iStart);
	}catch(Exception& e){
		IAS_REPORT_EXCEPTION(e);
	}
}

/*************************************************************************/

void TCThreads::MyThread::iterate(int i) {
	IAS_TRACER;

//	::IAS::MemoryManagerFactoryBT<int>::PtrHolder p;
//	p=::IAS::MemoryManagerFactoryBT<int>::CreateTab(10);

	IAS_LOG(true,"I:"<<iStart<<","<<((unsigned int)pthread_self())<<","<<ptrObject->strInfo);
	int *pp;
//  IAS_MEM_NEW(pp,int); //waisted
//	IAS_MEM_NEW(p,int);

	ptrObject->strInfo+="*";


		if(i>0){
			while(rand() % 1000000 > 2)
				{/*loop*/}
		//	IAS_MEM_DELETE(p);
			iterate(i-1);
		}else{
			//IAS_THROW(InternalException(String("thread test!")));
		}


}
/*************************************************************************/
TCThreads::Object::Object(){
	IAS_TRACER;
	strInfo=TypeTools::IntToString(pthread_self());
	IAS_LOG(true,"\nCreated: "<<((unsigned int)pthread_self())<<", "<<(void*)this<<std::endl);
}
/*************************************************************************/
TCThreads::Object::~Object(){
	IAS_TRACER
	IAS_LOG(true,"\nDestroyed: "<<((unsigned int)pthread_self())<<", "<<(void*)this<<strInfo);
}
/*************************************************************************/
}
}
