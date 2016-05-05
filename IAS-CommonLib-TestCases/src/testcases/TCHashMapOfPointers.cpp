/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCHashMapOfPointers.cpp
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

#include "TCHashMapOfPointers.h"

namespace IAS{
namespace TCT{

/*************************************************************************/
	
TCHashMapOfPointers::TCHashMapOfPointers(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCHashMapOfPointers::~TCHashMapOfPointers()throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCHashMapOfPointers::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCHashMapOfPointers::caseALL);
	TestUnit::init("TCHashMapOfPointers",&theTestRunner,pTestSuite);
}
/*************************************************************************/
TCHashMapOfPointers::MyTestObject::MyTestObject(int id)throw():id(id){
		std::cout<<"New test object:"<<id<<"\n";
		this->id=id;
		TheCount++;
	};
/*************************************************************************/
int TCHashMapOfPointers::MyTestObject::TheCount;
/*************************************************************************/
TCHashMapOfPointers::MyTestObject::~MyTestObject() throw(){
	IAS_TRACER;
	TheCount--;
	std::cout<<"Deleted test object:"<<id<<"\n";
}
/*************************************************************************/
void TCHashMapOfPointers::caseALL(){
	
	IAS_TRACER;
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	
	IAS_MY_STACK().printStack(std::cout);
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

	IAS::MemoryManager::GetInstance()->clearNewFlag();

	IAS_DFT_FACTORY<MyTestObject>::PtrHolder ptrLast;

	{ /*BEGIN: holders collection scope*/

		std::cout<<"START\n";
		IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);
		HashMapOfPointers<int, MyTestObject> hmObjects;
		std::cout<<"HashMapOfPointers\n";
		IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

		for(int i=0; i<5; i++){\
			hmObjects[i]=IAS_DFT_FACTORY<MyTestObject>::Create(i);
		}

		for(int i=0; i<5; i++){\
			hmObjects[i]=IAS_DFT_FACTORY<MyTestObject>::Create(i);
		}

		if(MyTestObject::TheCount != 5)
			IAS_THROW(InternalException("MyTestObject::TheCount != 5"));

		std::cout<<"Objects: \n";
		IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

        std::cout<<"T["<<3<<"]="<<(hmObjects[3]->id)<<"\n";

		int i=0;
		for(HashMapOfPointers<int, MyTestObject>::iterator it=hmObjects.begin();
			it != hmObjects.end();
			it++){
		    MyTestObject *pObject = it->second;
	        std::cout<<"T["<<(i++)<<"]="<<(pObject->id)<<"\n";
		}
		i=0;
		ptrLast=hmObjects[2];
		hmObjects.forget(2);
		hmObjects.erase(4);

		hmObjects[6]=IAS_DFT_FACTORY<MyTestObject>::Create(6);
		hmObjects[6]=IAS_DFT_FACTORY<MyTestObject>::Create(1006);
		hmObjects[6]=(MyTestObject*)hmObjects[6];


		for(HashMapOfPointers<int, MyTestObject>::iterator it=hmObjects.begin();
			it != hmObjects.end();
			it++){
		    MyTestObject *pObject = it->second;
	        std::cout<<"T["<<it->first<<"]="<<(pObject->id)<<"\n";
		}

	}/*END: holders collection scope */

	if(MyTestObject::TheCount != 1)
		IAS_THROW(InternalException("MyTestObject::TheCount != 1"));

	std::cout<<"and the last one ...\n";
	ptrLast=0;

	if(MyTestObject::TheCount != 0)
		IAS_THROW(InternalException("MyTestObject::TheCount != 0"));

	std::cout<<"End of test: \n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

}
/*************************************************************************/


} /* namespace TCT */
} /* namespace IAS */
