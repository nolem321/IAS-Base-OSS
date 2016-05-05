/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCProperties.cpp
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

#include "TCProperties.h"

namespace IAS {
namespace TCT {

/*************************************************************************/

TCProperties::TCProperties(TestSuite* pTestSuite) :theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCProperties::~TCProperties() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void TCProperties::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCProperties::caseALL);
	TestUnit::init("TCProperties",&theTestRunner,pTestSuite);
}

/*************************************************************************/
void TCProperties::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<PropertiesProvider>::PtrHolder ptrPP(IAS_DFT_FACTORY<PropertiesProviderFromFile>::Create("data/config/cfg1.txt"));
	IAS_DFT_FACTORY<Properties>::PtrHolder ptrExecutor(IAS_DFT_FACTORY<Properties>::Create(ptrPP.getPointer()));
}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
