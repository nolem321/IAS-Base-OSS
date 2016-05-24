/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCMisc.cpp
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

#include "TCMisc.h"
#include <unistd.h>

namespace IAS{
namespace TCT{

/*************************************************************************/

TCMisc::TCMisc(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCMisc::~TCMisc() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCMisc::init(TestSuite* pTestSuite){
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCMisc::caseALL);
	TestUnit::init("TCMisc",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCMisc::caseALL(){

	IAS_TRACER;
	std::cout<<IAS::MiscTools::StrToHex("\033AB\n\r\n\003abąło")<<'\n';
	std::cout<<IAS::MiscTools::StrToPrintableAndHex("\033AB\n\r\n\003abąło")<<'\n';
	std::cout<<IAS::MiscTools::StrToPrintableOrHex("\033AB\n\r\n\003abąło")<<'\n';

	std::cout<<TypeTools::Replace("abc1234abc56789abc","abc","XYZ")<<'\n';
	std::cout<<TypeTools::Replace("1234abc56789","abc","XYZ")<<'\n';

	{

		String strPattern("${home} sweet ${HOME}");
		String strValue = EnvTools::Substitute(strPattern);

		if(strValue.compare(" sweet "+EnvTools::GetEnv("HOME")) != 0)
			IAS_THROW(InternalException("Test case failed for  EnvTools::Substitute"));

		std::cout<<"Value: "<<strValue<<std::endl;

	}

	TimeSamplesResults tsr;
	TimeSample ts(true);
	std::cout<<"Wait !"<<std::endl;
	sleep(1);
	tsr.addSample(ts);
	sleep(2);
	tsr.addSample(ts);
	std::cout<<tsr<<std::endl;

}
/*************************************************************************/
} /* namespace TCT */
} /* namespace IAS */
