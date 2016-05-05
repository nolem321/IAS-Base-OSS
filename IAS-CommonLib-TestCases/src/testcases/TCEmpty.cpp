/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCEmpty.cpp
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

#include "TCEmpty.h"

namespace IAS{
namespace TCT{

/*************************************************************************/
	
TCEmpty::TCEmpty(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCEmpty::~TCEmpty() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCEmpty::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCEmpty::caseALL);
	TestUnit::init("TCEmpty",&theTestRunner,pTestSuite);
}

/*************************************************************************/
void TCEmpty::caseALL(){
	
	IAS_TRACER;
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	
	IAS_MY_STACK().printStack(std::cout);
	try{
		iterate(10);
	}catch(Exception& e){
		IAS_REPORT_EXCEPTION(e);
	}
	
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);
	std::cout<<"Secondcall:\n";	
	IAS::MemoryManager::GetInstance()->clearNewFlag();
	try{
			iterate(5);
	}catch(Exception& e){
		IAS_REPORT_EXCEPTION(e);
	}
	std::cout<<"ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout<<"New:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout,true);
		
}

/*************************************************************************/
void TCEmpty::iterate(int i){	
	
	IAS_TRACER;
	TCEmpty *e=NULL;
	
	//IAS_MEM_NEW(e,TCEmpty);
	
	if(i>0)
		iterate(i-1);
	else{
		IAS_THROW(InternalException(String("testowy")));
	}
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
