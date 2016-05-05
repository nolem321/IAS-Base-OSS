/*
 * File: IAS-CommonLib/src/commonlib/testcase/TestSuite.cpp
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
#include "TestSuite.h"

#include <commonlib/commonlib.h>
#include "TestUnit.h"
#include "commonlib/time/Timestamp.h"

namespace IAS {

/*************************************************************************/
TestSuite::TestSuite(){
	IAS_TRACER;
}
/*************************************************************************/
TestSuite::~TestSuite() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void TestSuite::addTestUnit(TestUnit *pTestUnit) {
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pTestUnit);

	if(hmTestUnits.count(pTestUnit->getName())!=0){
		IAS_THROW(BadUsageException(String("TestUnit alread exists: ")+=pTestUnit->getName()));
	}

	hmTestUnits[pTestUnit->getName()]=pTestUnit;

	const StringList& lstCases = pTestUnit->getCases();

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(), "Adding: "<<pTestUnit->getName()<<", no cases="<<lstCases.size());

	for (StringList::const_iterator it = lstCases.begin(); it != lstCases.end(); it++) {

		TestCase aNewTestCase;

		aNewTestCase.pTestUnit = pTestUnit;
		aNewTestCase.strName = *it;
		aNewTestCase.iResult = RESULT_NOT_EXECUTED;
		aNewTestCase.iNewMemoryEntries=0;
		aNewTestCase.iTimeMS=0;
		lstTestCases.push_back(aNewTestCase);
	}

}
/*************************************************************************/
void TestSuite::run(const String& strCaseName) {
	IAS_TRACER;

	for (TestCasesList::iterator it = lstTestCases.begin(); it != lstTestCases.end(); it++) {

		if(!strCaseName.empty() && strCaseName.compare((*it).pTestUnit->getName())!=0)
			continue;

		IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(), "TEST Started: "<<(*it).pTestUnit->getName()<<":"<<(*it).strName);



		try {

			MemoryManager::GetInstance()->clearNewFlag();
			TimeSample ts(true);
			(*it).pTestUnit->run((*it).strName);
			(*it).iTimeMS=ts.getSample()/1000;
			(*it).iResult = RESULT_OK;
			(*it).iNewMemoryEntries=MemoryManager::GetInstance()->getNumerOfNew();

		} catch (Exception& e) {

			StringStream ssInfo;
			e.printToStream(ssInfo);
			(*it).strInfo = ssInfo.str();
			(*it).iResult = RESULT_FAILED;

		} catch (std::exception& e) {

			(*it).strInfo = e.what();
			(*it).iResult = RESULT_FAILED;

		} catch (...) {

			(*it).strInfo = "unhandled exception";
			(*it).iResult = RESULT_FAILED;
		}

		IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(), "TEST Ended: "<<(*it).strName);
	}
}
/*************************************************************************/
void TestSuite::printResults(std::ostream& os) {
	IAS_TRACER;

	for (TestCasesList::iterator it = lstTestCases.begin(); it != lstTestCases.end(); it++) {

		char sBuffer[1024];
		snprintf(sBuffer, 1024, "%48s : %30s | %d : %ld : %6ld : %s \n", (*it).pTestUnit->getName().c_str(),
				(*it).strName.c_str(), (*it).iResult, (*it).iNewMemoryEntries, (*it).iTimeMS,(*it).strInfo.c_str());

		os << sBuffer;

	}
}
/*************************************************************************/
}
