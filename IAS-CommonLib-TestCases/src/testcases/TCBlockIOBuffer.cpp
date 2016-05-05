/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBlockIOBuffer.cpp
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
#include "commonlib/net/BlockIOBuffer.h"
#include "commonlib/net/FileHandle.h"

#include "TCBlockIOBuffer.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>

namespace IAS{
using namespace Net;
namespace TCT{

/*************************************************************************/
TCBlockIOBuffer::TCBlockIOBuffer(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);

}
/*************************************************************************/
TCBlockIOBuffer::~TCBlockIOBuffer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void TCBlockIOBuffer::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("c01",&::IAS::TCT::TCBlockIOBuffer::case01);
	theTestRunner.addCase("c02",&::IAS::TCT::TCBlockIOBuffer::case02);
	theTestRunner.addCase("c03",&::IAS::TCT::TCBlockIOBuffer::case03);
	theTestRunner.addCase("c04",&::IAS::TCT::TCBlockIOBuffer::case04);
	TestUnit::init("TCBlockIOBuffer",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCBlockIOBuffer::case01(){
	IAS_TRACER;


	String strMaster;
    InputFile::LoadString("/etc/passwd",strMaster);


    IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFileHandle(IAS_DFT_FACTORY<FileHandle>::Create(open("/etc/passwd",O_RDONLY)));

	IAS_DFT_FACTORY<BlockIOBuffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<BlockIOBuffer>::Create(
			ptrFileHandle.getPointer(),40));

	std::istream is(ptrBuffer);

	String strValue;

	char sBuffer[110];

	std::streamsize n;
	while(is.read(sBuffer,110).gcount() > 0){
		sBuffer[is.gcount()]=0;
		std::cerr<<"["<<sBuffer<<"]"<<std::endl;
		std::cerr.flush();
		strValue+=sBuffer;
	}


	if(strValue.compare(strMaster) != 0)
		IAS_THROW(InternalException("Values do not match."));

}
/*************************************************************************/
void TCBlockIOBuffer::case02(){
	IAS_TRACER;

	String strMaster;
    InputFile::LoadString("/etc/passwd",strMaster);


    IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFileHandle(IAS_DFT_FACTORY<FileHandle>::Create(open("/etc/passwd",O_RDONLY)));

   	IAS_DFT_FACTORY<BlockIOBuffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<BlockIOBuffer>::Create(
   			ptrFileHandle.getPointer(),40));

	std::istream is(ptrBuffer);

	String strValue;

	while(is.good()){
		int c=is.get();
		if(c != EOF)
			strValue+=c;
	}
	std::cerr<<strValue<<std::endl;

	if(strValue.compare(strMaster) != 0)
		IAS_THROW(InternalException("Values do not match."));

}
/*************************************************************************/
static void testWriteAtOnce(int iSize){
	IAS_TRACER;

	String strMaster;
    InputFile::LoadString("/etc/passwd",strMaster);

    strMaster=strMaster.substr(0,iSize);


    IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFileHandle(IAS_DFT_FACTORY<FileHandle>::Create(
    		open("/tmp/testcases.12345.txt",O_WRONLY|O_CREAT|O_TRUNC,0644)));

   	IAS_DFT_FACTORY<BlockIOBuffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<BlockIOBuffer>::Create(
   			ptrFileHandle.getPointer(),40));

    std::ostream os(ptrBuffer);

    os<<strMaster;
    os.flush();

    String strValue;
    InputFile::LoadString("/tmp/testcases.12345.txt",strValue);

	if(strValue.compare(strMaster) != 0)
		IAS_THROW(InternalException("Values do not match."));

}
/*************************************************************************/
void TCBlockIOBuffer::case03(){
	IAS_TRACER;

	testWriteAtOnce(0);
	testWriteAtOnce(1);
	testWriteAtOnce(10);
	testWriteAtOnce(39);
	testWriteAtOnce(40);
	testWriteAtOnce(41);
	testWriteAtOnce(79);
	testWriteAtOnce(80);
	testWriteAtOnce(81);
	testWriteAtOnce(1000);
	testWriteAtOnce(10000);
}
/*************************************************************************/
static void testWriteByChar(int iSize){
	IAS_TRACER;

	String strMaster;
    InputFile::LoadString("/etc/passwd",strMaster);

    strMaster=strMaster.substr(0,iSize);

    IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFileHandle(IAS_DFT_FACTORY<FileHandle>::Create(
    		open("/tmp/testcases.12345.txt",O_WRONLY|O_CREAT|O_TRUNC,0644)));

   	IAS_DFT_FACTORY<BlockIOBuffer>::PtrHolder ptrBuffer(IAS_DFT_FACTORY<BlockIOBuffer>::Create(
   			ptrFileHandle.getPointer(),40));

    std::ostream os(ptrBuffer);

    for(String::const_iterator it=strMaster.begin();
    	it != strMaster.end(); it++)
    	os<<(*it);

    os.flush();

    String strValue;
    InputFile::LoadString("/tmp/testcases.12345.txt",strValue);

	if(strValue.compare(strMaster) != 0)
		IAS_THROW(InternalException("Values do not match."));

}
/*************************************************************************/
void TCBlockIOBuffer::case04(){
	IAS_TRACER;


	testWriteByChar(0);
	testWriteByChar(1);
	testWriteByChar(10);
	testWriteByChar(39);
	testWriteByChar(40);
	testWriteByChar(41);
	testWriteByChar(79);
	testWriteByChar(80);
	testWriteByChar(81);
	testWriteByChar(1000);
	testWriteByChar(10000);

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
