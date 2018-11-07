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
void TCUrl::testUrl2(){
	IAS_TRACER;

	URI url("http://localhost/dane?operacja=tajfun&operation_number=M9947-82697&operation_type=payment&operation_status=completed&operation_amount=29.00&operation_currency=PLN&operation_withdrawal_amount=28.42&operation_commission_amount=-0.58&operation_original_amount=29.00&operation_original_currency=PLN&operation_datetime=2018-06-20+11%3A28%3A48&control=446540153&description=Alerty+o+Kontrahencie&email=anetttta%2Bdotpay%40wp.pl&p_info=Test+User+%28piotr.kasprzyk%40comit.pl%29&p_email=piotr.kasprzyk%40comit.pl&channel=73&signature=dce2a89a943f1cbc1f8d4cef3f2b8fe01c8fd746d25cf42c76ec3025ef9e54c9");

	std::cerr<<url.getValue("email")<<std::endl;
	std::cerr<<url.getValue("description")<<std::endl;
}
/*************************************************************************/
void TCUrl::caseALL(){

	IAS_TRACER;

	testUrl("pro://dom:100/path1/path2","pro","dom",100,"path1/path2");
	testUrl("pro://dom/path1/path2","pro","dom",0,"path1/path2");
	testUrl("pro:///path1/path2","pro","",0,"path1/path2");

	testUrl2();
}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
