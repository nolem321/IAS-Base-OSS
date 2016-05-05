/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCProcessList.cpp
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

#include "TCProcessList.h"

#include "commonlib/sys/proc/ProcessList.h"

namespace IAS {
using namespace SYS::Proc;
namespace TCT {

/*************************************************************************/

TCProcessList::TCProcessList(TestSuite* pTestSuite) :
	theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCProcessList::~TCProcessList() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void TCProcessList::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCProcessList::caseALL);
	TestUnit::init("TCProcessList",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCProcessList::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<ProcessList>::PtrHolder ptrProcessList(IAS_DFT_FACTORY<ProcessList>::Create());

	ptrProcessList->read();

	const ProcessList::EntriesList& lstEntries = ptrProcessList->getEntries();

	for (ProcessList::EntriesList::const_iterator it = lstEntries.begin(); it != lstEntries.end(); it++) {

		std::cout << (*it)->iPid << " : " << (*it)->strName << " ( " << (*it)->iStartTime;
		if ((*it)->iParentPid > 0)
			std::cout << " => " << (*it)->iParentPid << " : " << ptrProcessList->getEntryByPid((*it)->iParentPid)->strName;
		std::cout << std::endl;
	}

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
