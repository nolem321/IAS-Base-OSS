/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCPtrHoldersCollection.cpp
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

#include "TCPtrHoldersCollection.h"

namespace IAS{
namespace TCT{

/*************************************************************************/
	
TCPtrHoldersCollection::TCPtrHoldersCollection(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCPtrHoldersCollection::~TCPtrHoldersCollection() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCPtrHoldersCollection::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCPtrHoldersCollection::caseALL);
	TestUnit::init("TCPtrHoldersCollection",&theTestRunner,pTestSuite);
}
/*************************************************************************/
TCPtrHoldersCollection::MyTestObject::~MyTestObject() throw(){
	IAS_TRACER;
	std::cout<<"Deleted test object:"<<id<<"\n";
}
/*************************************************************************/
void TCPtrHoldersCollection::caseALL(){
	
	IAS_TRACER;
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	
	IAS_MY_STACK().printStack(std::cout);
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

	IAS::MemoryManager::GetInstance()->clearNewFlag();

	{/*BEGIN: holders collection scope */

		IAS_DFT_FACTORY<MyTestObject>::PtrHoldersCollection phcTestObjects;

		for(int i=0; i<5; i++){
			phcTestObjects.addPointer(IAS_DFT_FACTORY<MyTestObject>::Create(i));
		}

		int i=0;
		for(IAS_DFT_FACTORY<MyTestObject>::PtrHoldersCollection::iterator it=phcTestObjects.begin();
			it != phcTestObjects.end();
			it++){
		    MyTestObject *pObject = *it;
	        std::cout<<"T["<<(i++)<<"]="<<(pObject->id)<<"\n";
		}


	}/*END: holders collection scope */
}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
