/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCStorage.cpp
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

#include "TCStorage.h"
#include <qs/api.h>

namespace IAS{
using namespace QS::API;

namespace TCT{


/*************************************************************************/
TCStorage::TCStorage(TestSuite* pTestSuite):
	theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCStorage::~TCStorage() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCStorage::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("caseOne",&::IAS::TCT::TCStorage::caseOne);
	theTestRunner.addCase("caseTwo",&::IAS::TCT::TCStorage::caseTwo);
	theTestRunner.addCase("caseThree",&::IAS::TCT::TCStorage::caseThree);
	TestUnit::init("TCStorage",&theTestRunner,pTestSuite);
}


/*************************************************************************/
void TCStorage::caseOne(){
	

	Environment* TheEnvironment = Environment::GetInstance();

	URI uri;
	uri.setProtocol("shm");
	uri.setHost("sample");

	Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
	ContentManager* pContentManager = ptrConnection->getContentManager();

	TheEnvironment->shutdown();

    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
struct Data{
	int i,j;

	friend std::ostream& operator<<(std::ostream& os, const Data& d){
		os<<d.i<<" "<<d.j				;
		return os;
	}

	friend std::istream& operator>>(std::istream& is, Data& d){
		is>>d.i;
		is>>d.j;
		return is;
	}
};

/*************************************************************************/
void TCStorage::caseTwo(){

	{

		Environment* TheEnvironment = Environment::GetInstance();
		TheEnvironment->shutdown();

		URI uri;
		uri.setProtocol("shm");
		uri.setHost("sample");

		Connection::PtrHolder ptrConnection(TheEnvironment->connect(Environment::BuildConnection("shm","sample")));
		ContentManager* pContentManager = ptrConnection->getContentManager();

		IAS_DFT_FACTORY<Content>::PtrHoldersCollection phcContents;
		for (int i = 0; i < 7; i++) {
			IAS_DFT_FACTORY<Content>::PtrHolder	ptrContent(pContentManager->allocate());
			Data d;
			d.i=i;
			d.j=2*i;
			(*ptrContent)<<d;
			(*ptrContent).flush();
			phcContents.addPointer(ptrContent.pass());
		}

		int i=0;

		for(IAS_DFT_FACTORY<Content>::PtrHoldersCollection::iterator it=phcContents.begin();
				it != phcContents.end(); it++){
			Data d;
			*(*it)>>d;
			std::cerr<<"i="<<i++<<", "<<d.i<<","<<d.j<<std::endl;
		}

	}
    std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/
void TCStorage::caseThree(){

	return;

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
