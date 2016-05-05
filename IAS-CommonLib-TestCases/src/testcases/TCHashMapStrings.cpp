/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCHashMapStrings.cpp
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

#include "TCHashMapStrings.h"

namespace IAS{
namespace TCT{

/*************************************************************************/
	
TCHashMapStrings::TCHashMapStrings(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCHashMapStrings::~TCHashMapStrings()throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCHashMapStrings::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCHashMapStrings::caseALL);
	TestUnit::init("TCHashMapStrings",&theTestRunner,pTestSuite);
}
/*************************************************************************/
TCHashMapStrings::MyTestObject::~MyTestObject() throw(){
	IAS_TRACER;
	std::cout<<"Deleted test object:"<<id<<"\n";
}
/*************************************************************************/
void TCHashMapStrings::caseALL(){
	
	IAS_TRACER;
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	
	IAS_MY_STACK().printStack(std::cout);
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);

	IAS::MemoryManager::GetInstance()->clearNewFlag();

	{ /*BEGIN: holders collection scope*/

		HashMapStringToPointer<MyTestObject> hmObjects;

		for(int i=0; i<5; i++){\
			IAS_DFT_FACTORY<MyTestObject>::PtrHolder ptrObject(IAS_DFT_FACTORY<MyTestObject>::Create(i));

			StringStream ss;
			ss<<"Obj:"<<i;
			hmObjects[ss.str()]=ptrObject.pass();
		}

        std::cout<<"T["<<"Obj:3"<<"]="<<(hmObjects["Obj:3"]->id)<<"\n";

		int i=0;
		for(HashMapStringToPointer<MyTestObject>::iterator it=hmObjects.begin();
			it != hmObjects.end();
			it++){
		    MyTestObject *pObject = it->second;
	        std::cout<<"T["<<(i++)<<"]="<<(pObject->id)<<"\n";
		}


	}/*END: holders collection scope */

	{ /*BEGIN: holders collection scope*/

		HashMapStringPairToPointer<MyTestObject> hmObjects;

		for(int i=0; i<5; i++){\
			IAS_DFT_FACTORY<MyTestObject>::PtrHolder ptrObject(IAS_DFT_FACTORY<MyTestObject>::Create(i));

			StringStream ss;
			ss<<"Obj:"<<i;

			//hmObjects[HashMapStringPairToPointer<MyTestObject>::Key(ss.str(),ss.str())]=ptrObject.getPointer();

			HashMapStringPairToPointer<MyTestObject>::Key key(ss.str(),ss.str());
			hmObjects[key]=ptrObject.pass();
			hmObjects.hasKey(key);
		}

        std::cout<<"T["<<"Obj:3"<<"]="<<(hmObjects.atKey("Obj:3","Obj:3")->id)<<"\n";

		int i=0;
		for(HashMapStringPairToPointer<MyTestObject>::iterator it=hmObjects.begin();
			it != hmObjects.end();
			it++){
		    MyTestObject *pObject = it->second;
	        std::cout<<"T["<<it->first<<"]="<<(pObject->id)<<"\n";
		}


	}/*END: holders collection scope */
		
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
