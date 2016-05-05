/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCStreamMemoryBuffer.cpp
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
#include "commonlib/memory/buffer/StreamMemoryBuffer.h"

#include "TCStreamMemoryBuffer.h"

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
namespace TCT{

/*************************************************************************/
TCStreamMemoryBuffer::TCStreamMemoryBuffer(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCStreamMemoryBuffer::~TCStreamMemoryBuffer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCStreamMemoryBuffer::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("c01",&::IAS::TCT::TCStreamMemoryBuffer::case01);
	theTestRunner.addCase("c02",&::IAS::TCT::TCStreamMemoryBuffer::case02);
	theTestRunner.addCase("c03",&::IAS::TCT::TCStreamMemoryBuffer::case03);
	theTestRunner.addCase("c04",&::IAS::TCT::TCStreamMemoryBuffer::case04);
	TestUnit::init("TCStreamMemoryBuffer",&theTestRunner,pTestSuite);
}
static String CTestData(
		"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ!L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ@L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ#L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ$L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ%L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ^L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ&L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ*L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ(L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ)L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ!L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ@L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ#L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ$L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ%L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ^L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ&L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ*L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ(L"
				"1234567890abcdefghijABCDEFGHIJKL1234567890abcdefghijABCDEFGHIJ)L");
/*************************************************************************/
static void  case01logic(size_t iInitSegSize, size_t iInputBufSize, size_t iOutputBufSize){
	IAS_TRACER;

	//std::cerr<<"Testing MBuf: "<<iInitSegSize<<", "<<iInputBufSize<<", "<<iOutputBufSize<<std::endl;

	void *pStreamMemoryBuffer=StreamMemoryBuffer::Create(MemoryManager::GetInstance(),iInitSegSize);
	{
	IAS_DFT_FACTORY<StreamMemoryBuffer>::PtrHolder ptrSMB(
			IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pStreamMemoryBuffer,
					MemoryManager::GetInstance()));

	std::ostream os(ptrSMB);

	for(int iIdx=0; iIdx<CTestData.length(); iIdx+=iInitSegSize){
		os<<CTestData.substr(iIdx,iInitSegSize);
	}

	os.flush();

	char sBuffer[iOutputBufSize+1];
	std::istream is(ptrSMB);

	StringStream ssResult;

	while(is.read(sBuffer,iOutputBufSize).gcount() > 0){
		sBuffer[is.gcount()]=0;
		ssResult<<sBuffer;
		//std::cerr<<"["<<sBuffer<<"]"<<std::endl;
		//std::cerr.flush();
	}

	ssResult.flush();

	if(CTestData.compare(ssResult.str()) != 0){
		StringStream ssMsg;
		ssMsg<<"Match error for [1]: "<<iInitSegSize<<", "<<iInputBufSize<<", "<<iOutputBufSize;
		IAS_THROW(BadUsageException(ssMsg.str()));
	}

	}

	StreamMemoryBuffer::Destroy(pStreamMemoryBuffer,MemoryManager::GetInstance());
}

/*************************************************************************/
void TCStreamMemoryBuffer::case01(){
	IAS_TRACER;

	std::cerr<<"Case 01 -at least 20 sec."<<std::endl;

	for(int iInit=10; iInit <= CTestData.length();iInit <<= 1)
		for(int iInput=10; iInput < CTestData.length(); iInput < 10 ? iInput+=1 : iInput += 7)
			for(int iOutput=10; iOutput < CTestData.length();iOutput < 10 ? iOutput+=1 : iOutput += 15 )
				case01logic(iInit,iInput,iOutput);

}

/*************************************************************************/
/*************************************************************************/
static void  case02logic(size_t iInitSegSize){
	IAS_TRACER;

	//std::cerr<<"Testing MBuf: "<<iInitSegSize<<", "<<iInputBufSize<<", "<<iOutputBufSize<<std::endl;

	void *pStreamMemoryBuffer=StreamMemoryBuffer::Create(MemoryManager::GetInstance(),iInitSegSize);
	{
	IAS_DFT_FACTORY<StreamMemoryBuffer>::PtrHolder ptrSMB(
			IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pStreamMemoryBuffer,
					MemoryManager::GetInstance()));

	std::ostream os(ptrSMB);

	for(String::const_iterator it=CTestData.begin();
		it != CTestData.end(); it++)
		os.put(*it);

	os.flush();

	StringStream ssResult;

	std::istream is(ptrSMB);

	int c;
	int iCounter=0;

	while( (c=is.get()) != EOF ){

		is.unget();
		c=is.get();

		ssResult<<(char)c;
	}

	ssResult.flush();

	if(CTestData.compare(ssResult.str()) != 0){
		StringStream ssMsg;
		ssMsg<<"Match error for [2] :"<<iInitSegSize;
		IAS_THROW(BadUsageException(ssMsg.str()));
	}

	}

	StreamMemoryBuffer::Destroy(pStreamMemoryBuffer,MemoryManager::GetInstance());
}
/*************************************************************************/
void TCStreamMemoryBuffer::case02(){
	IAS_TRACER;


	for(int iInit=10; iInit <= CTestData.length();iInit += 1)
		case02logic(iInit);

}
/*************************************************************************/
void TCStreamMemoryBuffer::case03(){
	IAS_TRACER;


	void *pStreamMemoryBuffer=StreamMemoryBuffer::Create(MemoryManager::GetInstance(),65);

	IAS_DFT_FACTORY<StreamMemoryBuffer>::PtrHolder ptrSMB(
			IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pStreamMemoryBuffer,
					MemoryManager::GetInstance()));

	std::ostream os(ptrSMB);

	os<<CTestData;

	os.flush();

	std::istream is(ptrSMB);

	String strInfo1;
	is>>strInfo1;


	//std::cerr<<"--------------"<<std::endl;

	//ptrSMB=IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pStreamMemoryBuffer,MemoryManager::GetInstance());

	//std::istream is(ptrSMB);

	is.clear();
	is.seekg(0);


	String strInfo2;
	is>>strInfo2;

	if(CTestData.compare(strInfo1) != 0){
			StringStream ssMsg;
			ssMsg<<"Match error for [3a] :"<<strInfo1;
			IAS_THROW(BadUsageException(ssMsg.str()));
		}

	if(CTestData.compare(strInfo2) != 0){
			StringStream ssMsg;
			ssMsg<<"Match error for [3b] :"<<strInfo2.length()<<" "<<strInfo1.length();
			IAS_THROW(BadUsageException(ssMsg.str()));
		}

}
/*************************************************************************/
static void case04logic(size_t iInitSize, const String& strOne, const String& strTwo){
	IAS_TRACER;

	//TODO memory leak in this case !!!
	void *pStreamMemoryBuffer=StreamMemoryBuffer::Create(MemoryManager::GetInstance(),iInitSize);

		IAS_DFT_FACTORY<StreamMemoryBuffer>::PtrHolder ptrSMB(
				IAS_DFT_FACTORY<StreamMemoryBuffer>::Create(pStreamMemoryBuffer,
						MemoryManager::GetInstance()));

		std::ostream os(ptrSMB);

		os<<CTestData;
		os.flush();
		os.seekp(0);
		os<<strOne;
		os.seekp(0,os.end);
		os<<strTwo;
		os.flush();

		std::istream is(ptrSMB);

		String strInfo;
		is>>strInfo;

		if(strInfo.compare(strOne+CTestData.substr(strOne.length())+strTwo) != 0){
			StringStream ssMsg;
			ssMsg<<"Match error for [4a] :"<<strOne<<", "<<strTwo<<", il="<<iInitSize;
			IAS_THROW(BadUsageException(ssMsg.str()));
		}

}
/*************************************************************************/
void TCStreamMemoryBuffer::case04(){
	IAS_TRACER;

	std::cerr<<"Case 04 -at least 20 sec."<<std::endl;

	for(int iInit=10; iInit <= CTestData.length();iInit+=16)
			for(int iOne=1; iOne < CTestData.length() / 4; iOne+=8)
				for(int iTwo=1; iTwo < CTestData.length() / 8; iTwo+=6 )
					case04logic(iInit,CTestData.substr(0,iOne),CTestData.substr(0,iTwo));

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
