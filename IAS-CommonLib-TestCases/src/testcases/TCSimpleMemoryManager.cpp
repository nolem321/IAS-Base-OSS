/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSimpleMemoryManager.cpp
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
#include "commonlib/memory/mm/SimpleListMemoryManager.h"

#include "TCSimpleMemoryManager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
Allocator *TCSimpleMemoryManager::TheAllocator;
/*************************************************************************/
TCSimpleMemoryManager::TCSimpleMemoryManager(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCSimpleMemoryManager::~TCSimpleMemoryManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCSimpleMemoryManager::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCSimpleMemoryManager::caseALL);
	TestUnit::init("TCSimpleMemoryManager",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCSimpleMemoryManager::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<SimpleListMemoryManager>::PtrHolder ptrMemoryManager;
	char *b = new char[40000];
	SimpleListMemoryManager::Initialize((void*)b,(size_t)40000);

	ptrMemoryManager=IAS_DFT_FACTORY<SimpleListMemoryManager>::Create(b);
	TheAllocator=ptrMemoryManager;

	{
		AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc;
		for(int i=0;i<10;i++){
			phc.addPointer(AllocatorFactory<Object,&GetAllocator>::Create(i));
		}
	}

	{
		AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc;
		for(int i=0;i<10;i++){
			phc.addPointer(AllocatorFactory<Object,&GetAllocator>::Create(100+i));
		}
	}

	typedef AllocatorFactory<Object, &GetAllocator > MMA;

	typedef std::basic_string< char,
					std::char_traits<char>,
					AllocatorFactory< char, &GetAllocator >
				> StringObject;
	{
		StringObject str;

		for(int i=0;i<10;i++){
			StringObject str1((TypeTools::IntToString(i*i)+"abcdef").c_str());
			str1+="121314123412341234123412341234123412";
			str1=str1+str1+str1;
			str+=str1;
		}
	}

	AllocatorFactory<Object,&GetAllocator >::Create(100);
	TheAllocator=ptrMemoryManager=IAS_DFT_FACTORY<SimpleListMemoryManager>::Create(b);
	AllocatorFactory<Object,&GetAllocator >::Create(100);

	try{
		ptrMemoryManager->allocate(139000);
	}catch(std::bad_alloc &e){}
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
