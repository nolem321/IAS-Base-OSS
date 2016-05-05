/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCHttp.cpp
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
#include "commonlib/net/http/http.h"

#include "TCHttp.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace IAS{
using namespace Net;
namespace TCT{

/*************************************************************************/

TCHttp::TCHttp(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCHttp::~TCHttp() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCHttp::init(TestSuite* pTestSuite){
	IAS_TRACER;

	theTestRunner.addCase("Request",&::IAS::TCT::TCHttp::caseRequest);
	theTestRunner.addCase("Response",&::IAS::TCT::TCHttp::caseResponse);
	//theTestRunner.addCase("Chunked",&::IAS::TCT::TCHttp::caseChunked);
	theTestRunner.addCase("KnownLength",&::IAS::TCT::TCHttp::caseKnownLength);
	TestUnit::init("TCHttp",&theTestRunner,pTestSuite);
}
/*************************************************************************/
static void _testRequestParser(const String& strText, const String& strInfo){
	IAS_TRACER;

	StringStream ssInput(strText);
	StringStream ssOutput;

	IAS_DFT_FACTORY<HTTP::Request>::PtrHolder ptrRequest(
					IAS_DFT_FACTORY<HTTP::Request>::Create());

	ptrRequest->parse(ssInput);
	ptrRequest->serialize(ssOutput);

	if(strText.compare(ssOutput.str()) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Good: "<<strText);
		IAS_LOG(LogLevel::INSTANCE.isError(),"Bad:  "<<ssOutput.str());
		IAS_THROW(InternalException(strInfo));
	}
}
/*************************************************************************/
static int _openTmpFile(bool bRead=false){

	static const char *sname = "/tmp/.tchttp123.dat";

	int fd=::open(sname, bRead ? O_RDONLY : (O_WRONLY | O_TRUNC |O_CREAT) ,0600);

	if(fd < 0)
		IAS_THROW(SystemException("Problem with a temporary file:")<<sname);

	return fd;
}
/*************************************************************************/
static void _testRequestPumpParser(const String& strText, const String& strInfo){
	IAS_TRACER;

	StringStream ssInText;


	try{
		IAS_DFT_FACTORY<HTTP::Request>::PtrHolder ptrRequest(
					IAS_DFT_FACTORY<HTTP::Request>::Create());

		StringStream ssOutText(strText);

		ptrRequest->parse(ssOutText);

		IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFile(
					IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile()));

		IAS_DFT_FACTORY<HTTP::HeaderOutputPump>::PtrHolder ptrOutputPump(
				IAS_DFT_FACTORY<HTTP::HeaderOutputPump>::Create(ptrRequest,ptrFile));

		ptrOutputPump->pump();

		ptrRequest = IAS_DFT_FACTORY<HTTP::Request>::Create();
		ptrFile     = IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile(true));

		IAS_DFT_FACTORY<HTTP::HeaderInputPump>::PtrHolder ptrInputPump(
				IAS_DFT_FACTORY<HTTP::HeaderInputPump>::Create(ptrRequest,ptrFile));

		ptrInputPump->pump();


		ptrRequest->serialize(ssInText);
	}catch(Exception& e){
		IAS_THROW(InternalException(strInfo+e.getName()+e.getInfo()));
	}

	if(strText.compare(ssInText.str()) != 0)
		IAS_THROW(InternalException(strInfo));

}
/*************************************************************************/
static const String _strReq1(
"GET /path/to/file/index.html HTTP/1.1\r\n"
"\r\n"
);
/*************************************************************************/
static const String _strReq2(
"POST /path/script.cgi HTTP/1.0\r\n"
"From: frog@jmarshall.com\r\n"
"User-Agent: HTTPTool/1.0\r\n"
"Content-Type: application/x-www-form-urlencoded\r\n"
"Content-Length: 32\r\n"
"\r\n"
);
/*************************************************************************/
void TCHttp::caseRequest(){
	IAS_TRACER;
	_testRequestParser(_strReq1,"Basic HTTP request header");
	_testRequestParser(_strReq2,"Typical HTTP request header");
	_testRequestPumpParser(_strReq2,"Typical HTTP request header  - pump");
}
/*************************************************************************/
/*************************************************************************/
static void _testResponseParser(const String& strText, const String& strInfo){
	IAS_TRACER;

	StringStream ssInput(strText);
	StringStream ssOutput;

	IAS_DFT_FACTORY<HTTP::Response>::PtrHolder ptrResponse(
					IAS_DFT_FACTORY<HTTP::Response>::Create());

	ptrResponse->parse(ssInput);
	ptrResponse->serialize(ssOutput);

	if(strText.compare(ssOutput.str()) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Good: "<<strText);
		IAS_LOG(LogLevel::INSTANCE.isError(),"Bad:  "<<ssOutput.str());
		IAS_THROW(InternalException(strInfo));
	}
}
/*************************************************************************/
static void _testResponsePumpParser(const String& strText, const String& strInfo){
	IAS_TRACER;


	IAS_DFT_FACTORY<HTTP::Response>::PtrHolder ptrResponse(
				IAS_DFT_FACTORY<HTTP::Response>::Create());

	StringStream ssOutText(strText);

	ptrResponse->parse(ssOutText);

	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFile(
				IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile()));

	IAS_DFT_FACTORY<HTTP::HeaderOutputPump>::PtrHolder ptrOutputPump(
			IAS_DFT_FACTORY<HTTP::HeaderOutputPump>::Create(ptrResponse,ptrFile));

	ptrOutputPump->pump();

	ptrResponse = IAS_DFT_FACTORY<HTTP::Response>::Create();
	ptrFile     = IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile(true));

	IAS_DFT_FACTORY<HTTP::HeaderInputPump>::PtrHolder ptrInputPump(
			IAS_DFT_FACTORY<HTTP::HeaderInputPump>::Create(ptrResponse,ptrFile));

	ptrInputPump->pump();

	StringStream ssInText;

	ptrResponse->serialize(ssInText);

	if(strText.compare(ssInText.str()) != 0)
		IAS_THROW(InternalException(strInfo));

}
/*************************************************************************/
static const String _strRes1(
"HTTP/1.0 200 OK\r\n"
"Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n"
"Content-Type: text/html\r\n"
"Content-Length: 1354\r\n"
"\r\n"
);
/*************************************************************************/
static const String _strRes2(
"HTTP/1.1 404 Not Found\r\n"
"Date: Fri, 31 Dec 1999 23:59:59 GMT\r\n"
"\r\n"
);
/*************************************************************************/
void TCHttp::caseResponse(){
	IAS_TRACER;

	_testResponseParser(_strRes1,"Typical HTTP response header");
	_testResponseParser(_strRes2,"404 HTTP response header");
	_testResponsePumpParser(_strRes1,"Typical HTTP response header  - pump");
}
/*************************************************************************/
static void _testChunkedPump(const String& strText, const String& strInfo){
	IAS_TRACER;


	StringStream ssOutText(strText);

	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFile(
				IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile()));

	IAS_DFT_FACTORY<HTTP::ChunkedOutputPump>::PtrHolder ptrOutputPump(
			IAS_DFT_FACTORY<HTTP::ChunkedOutputPump>::Create<Net::IBlockIO*,std::istream&>(ptrFile,ssOutText));

	ptrOutputPump->pump();

	ptrFile     = IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile(true));

	StringStream ssInText;

	IAS_DFT_FACTORY<HTTP::ChunkedInputPump>::PtrHolder ptrInputPump(
			IAS_DFT_FACTORY<HTTP::ChunkedInputPump>::Create<Net::IBlockIO*,std::ostream&>(ptrFile,ssInText));

	ptrInputPump->pump();

	if(strText.compare(ssInText.str()) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Good: "<<strText);
		IAS_LOG(LogLevel::INSTANCE.isError(),"Bad:  "<<ssInText.str());
		IAS_THROW(InternalException(strInfo));
	}

}

/*************************************************************************/
void TCHttp::caseChunked(){
	IAS_TRACER;

	const String strTestDataPart = "1234567890";
	String strData;

	for (int iIdx = 0; iIdx < 1000; ++iIdx) {
		strData+=strTestDataPart;
	}

	std::cout<<"Wait 60s ! "<<std::endl;

	for(int iIdx = 0; iIdx < strData.length(); ++iIdx){
		_testChunkedPump(strData.substr(iIdx),String("Chunked: ")+TypeTools::IntToString(iIdx));
	}

	strData=strTestDataPart;

	for (int iIdx = 0; iIdx < 10; ++iIdx) {
		strData+=strData;
	}

	for(int iIdx = 0; iIdx < strData.length(); iIdx+=100){
		_testChunkedPump(strData.substr(iIdx),String("Chunked: ")+TypeTools::IntToString(iIdx));
	}
}
/*************************************************************************/
static void _testKnownLengthChunkedPump(const String& strText, const String& strInfo){
	IAS_TRACER;


	StringStream ssOutText(strText);

	IAS_DFT_FACTORY<FileHandle>::PtrHolder ptrFile(
				IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile()));

	IAS_DFT_FACTORY<Async::KnownLengthOutputPump>::PtrHolder ptrOutputPump(
			IAS_DFT_FACTORY<Async::KnownLengthOutputPump>::Create<Net::IBlockIO*,std::istream&>(ptrFile,ssOutText,strText.length()));

	ptrOutputPump->pump();

	size_t tmp;
	ptrFile->write("Garbage",7,tmp);

	ptrFile     = IAS_DFT_FACTORY<FileHandle>::Create(_openTmpFile(true));

	StringStream ssInText;

	IAS_DFT_FACTORY<Async::KnownLengthInputPump>::PtrHolder ptrInputPump(
			IAS_DFT_FACTORY<Async::KnownLengthInputPump>::Create<Net::IBlockIO*,std::ostream&>(ptrFile,ssInText,strText.length()));

	ptrInputPump->pump();

	if(strText.compare(ssInText.str()) != 0){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Good: "<<strText);
		IAS_LOG(LogLevel::INSTANCE.isError(),"Bad:  "<<ssInText.str());
		IAS_THROW(InternalException(strInfo));
	}

}

/*************************************************************************/
void TCHttp::caseKnownLength(){
	IAS_TRACER;

	const String strTestDataPart = "1234567890";
	String strData;

	for (int iIdx = 0; iIdx < 1000; ++iIdx) {
		strData+=strTestDataPart;
	}

	std::cout<<"Wait 60s ! "<<std::endl;

	for(int iIdx = 0; iIdx < strData.length(); ++iIdx){
		_testKnownLengthChunkedPump(strData.substr(iIdx),String("Known Length: ")+TypeTools::IntToString(iIdx));
	}

	strData=strTestDataPart;

	for (int iIdx = 0; iIdx < 10; ++iIdx) {
		strData+=strData;
	}

	for(int iIdx = 0; iIdx < strData.length(); iIdx+=100){
		_testKnownLengthChunkedPump(strData.substr(iIdx),String("Known Length: ")+TypeTools::IntToString(iIdx));
	}
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
