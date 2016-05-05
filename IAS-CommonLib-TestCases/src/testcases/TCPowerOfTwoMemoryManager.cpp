/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCPowerOfTwoMemoryManager.cpp
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
#include "commonlib/memory/mm/PowerOfTwoMemoryManager.h"

#include "TCPowerOfTwoMemoryManager.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

#include <memory>

namespace IAS{
namespace TCT{

/*************************************************************************/
Allocator *TCPowerOfTwoMemoryManager::TheAllocator;
/*************************************************************************/
TCPowerOfTwoMemoryManager::TCPowerOfTwoMemoryManager(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCPowerOfTwoMemoryManager::~TCPowerOfTwoMemoryManager() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCPowerOfTwoMemoryManager::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("c01",&::IAS::TCT::TCPowerOfTwoMemoryManager::case01);
	theTestRunner.addCase("c02",&::IAS::TCT::TCPowerOfTwoMemoryManager::case02);
	TestUnit::init("TCPowerOfTwoMemoryManager",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCPowerOfTwoMemoryManager::case01logic(int iSize, int iNumObjects){
	IAS_TRACER;

	IAS_DFT_FACTORY<PowerOfTwoMemoryManager>::PtrHolder ptrMemoryManager;
	char *b= new char[iSize];
	PowerOfTwoMemoryManager::Initialize((void*)b,iSize,5);

	ptrMemoryManager=IAS_DFT_FACTORY<PowerOfTwoMemoryManager>::Create(b);
	TheAllocator=ptrMemoryManager;

	try {

		{
			AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc;
			for(int i=0;i<iNumObjects;i++) {
				phc.addPointer(AllocatorFactory<Object,&GetAllocator>::Create(i));
				TheAllocator->free(TheAllocator->allocate(1000));

			}


		}

		{
			AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc;
			for(int i=0;i<iNumObjects;i++) {
				phc.addPointer(AllocatorFactory<Object,&GetAllocator>::Create(100+i));
				TheAllocator->free(TheAllocator->allocate(1000));
			}
		}


		typedef AllocatorFactory<Object, &GetAllocator > MMA;

		typedef std::basic_string< char,
		std::char_traits<char>,
		AllocatorFactory< char, &GetAllocator >
		> StringObject;
		{
			StringObject str;

			for(int i=0;i<iSize/10000;i++) {
				StringObject str1((TypeTools::IntToString(i*i)+"abcdef").c_str());
				str1+="121314123412341234123412341234123412";
				str1=str1+str1+str1;
				str+=str1;
				TheAllocator->free(TheAllocator->allocate(1000));

			}

		}

	}catch(Exception& e){
		e.printToStream(std::cerr);
	}

	AllocatorFactory<Object,&GetAllocator >::Create(100);
	TheAllocator=ptrMemoryManager=IAS_DFT_FACTORY<PowerOfTwoMemoryManager>::Create(b);
	AllocatorFactory<Object,&GetAllocator >::Create(100);

	try{
		ptrMemoryManager->allocate(iSize/4);
		IAS_THROW(BadUsageException("std::bad_alloc was expected."))
	}catch(std::bad_alloc &e){}

}
/*************************************************************************/
void TCPowerOfTwoMemoryManager::case01(){
	IAS_TRACER;
	case01logic(400000,100);
	case01logic(800000,1000);
	case01logic(800000,2000);
}
/*************************************************************************/
void TCPowerOfTwoMemoryManager::case02(){
	IAS_TRACER;

	IAS_DFT_FACTORY<PowerOfTwoMemoryManager>::PtrHolder ptrMemoryManager;
	char * b =  new char[1600000];
	PowerOfTwoMemoryManager::Initialize((void*)b,1600000,5);

	ptrMemoryManager=IAS_DFT_FACTORY<PowerOfTwoMemoryManager>::Create(b);
	TheAllocator=ptrMemoryManager;

	const int iNumObjects=5000;
	std::vector<Object*> ptr1(iNumObjects);
	std::vector<Object*> ptr2(iNumObjects);

	{
		AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc1;
		{
			AllocatorFactory<Object,&GetAllocator>::PtrHoldersCollection phc2;

			for(int i=0;i<iNumObjects;i++) {
				ptr1[i]=AllocatorFactory<Object,&GetAllocator>::Create(100+i);
				phc1.addPointer(ptr1[i]);
				TheAllocator->free(TheAllocator->allocate(1000));
				ptr2[i]=AllocatorFactory<Object,&GetAllocator>::Create(2100+i);
				phc2.addPointer(ptr2[i]);
			}

			for(int i=0;i<iNumObjects;i++)
				if(!ptrMemoryManager->check(ptr1[i]) || !ptrMemoryManager->check(ptr2[i]))
					IAS_THROW(BadUsageException("Check 02a"));

		}

		for(int i=0;i<iNumObjects;i++)
			if(!ptrMemoryManager->check(ptr1[i]) || ptrMemoryManager->check(ptr2[i]))
				IAS_THROW(BadUsageException("Check 02b"));

	}



	for(int i=0;i<iNumObjects;i++)
		if(ptrMemoryManager->check(ptr1[i]))
			IAS_THROW(BadUsageException("Check 02c"));

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
