/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCRegionMemoryManager.cpp
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
#include "commonlib/memory/mm/RegionMemoryManager.h"

#include "TCRegionMemoryManager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
//Allocator *TCRegionMemoryManager::TheAllocator;
/*************************************************************************/
TCRegionMemoryManager::TCRegionMemoryManager(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCRegionMemoryManager::~TCRegionMemoryManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCRegionMemoryManager::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCRegionMemoryManager::caseALL);
	TestUnit::init("TCRegionMemoryManager",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCRegionMemoryManager::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<RegionMemoryManager>::PtrHolder ptrMemoryManager;
	ptrMemoryManager=IAS_DFT_FACTORY<RegionMemoryManager>::Create(IAS::MemoryManager::GetInstance(),256);
	IAS::MemoryManager::SetDefaultAllocator(ptrMemoryManager);

	try {

		{
			IAS_DFT_FACTORY<Object>::PtrHoldersCollection phc;
			for(int i=0;i<20;i++) {
				phc.addPointer(IAS_DFT_FACTORY<Object>::Create(i));
			}
		}

		{
			IAS_DFT_FACTORY<Object>::PtrHoldersCollection phc;
			for(int i=0;i<20;i++) {
				phc.addPointer(IAS_DFT_FACTORY<Object>::Create(100+i));
			}
		}


		typedef std::basic_string< char,
			std::char_traits<char>,
			AllocatorFactory< char, &IAS::MemoryManager::GetAllocator >
			>StringObject;

		{
			StringObject str;

			for(int i=0;i<10;i++) {
				StringObject str1((TypeTools::IntToString(i*i)+"abcdef").c_str());
				str1+="121314123412341234123412341234123412";
				str1=str1+str1+str1;
				str+=str1;
			}
		}

		ptrMemoryManager->freeAll();

		{
			StringObject str;

			for(int i=0;i<5;i++) {
				StringObject str1((TypeTools::IntToString(i*i)+"abcdef").c_str());
				str1+="12131412341234123412341234123zzzzzzzzzzzzzzzzzz";
				str1=str1+str1+str1;
				str+=str1;
			}

			ptrMemoryManager->dump(std::cerr);

			for(int i=0;i<7;i++) {
				StringObject str1((TypeTools::IntToString(i*i)+"abcdef").c_str());
				str1+="12131412341234123412341234123zzzzzzzzzzzzzzzzzz";
				str1=str1+str1+str1;
				str+=str1;
			}
		}

		ptrMemoryManager->dump(std::cerr);


	}catch(Exception& e){
		e.printToStream(std::cerr);
	}

	ptrMemoryManager->printToStream(std::cerr);

	IAS_DFT_FACTORY<Object>::Create(100);

//	ptrMemoryManager=IAS_DFT_FACTORY<RegionMemoryManager>::Create(
//			IAS::MemoryManager::GetInstance(),1000);

//	IAS::MemoryManager::SetDefaultAllocator(ptrMemoryManager);

	IAS_DFT_FACTORY<Object>::Create(100);

	try{
		ptrMemoryManager->allocate(139000);
	}catch(std::bad_alloc &e){}

	IAS::MemoryManager::SetDefaultAllocator(IAS::MemoryManager::GetInstance());

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
