/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCUrl.cpp
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

#include "TCUrl.h"

namespace IAS{
namespace TCT{

/*************************************************************************/

TCUrl::TCUrl(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCUrl::~TCUrl() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCUrl::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCUrl::caseALL);
	TestUnit::init("TCUrl",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCUrl::testUrl(const String& strUrl,
				    const String& strProtocol,
				    const String& strDomain,
				    unsigned int iPort,
				    const String& strPath){
	IAS_TRACER;

	URI url(strUrl);

	if(strProtocol.compare(url.getProtocol()))
		IAS_THROW(InternalException(String("Bad protocol: [")+strUrl+"], protocol=["+url.getProtocol()+"]"));

	if(strDomain.compare(url.getHost()))
		IAS_THROW(InternalException(String("Bad domain: [")+strUrl+"], domain=["+url.getHost()+"]"));

	if(strPath.compare(url.getPath()))
		IAS_THROW(InternalException(String("Bad path: [")+strUrl+"], path=["+url.getPath()+"]"));

}
/*************************************************************************/
void TCUrl::caseALL(){

	IAS_TRACER;

	testUrl("pro://dom:100/path1/path2","pro","dom",100,"path1/path2");
	testUrl("pro://dom/path1/path2","pro","dom",0,"path1/path2");
	testUrl("pro:///path1/path2","pro","",0,"path1/path2");


}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
