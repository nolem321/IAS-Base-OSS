/*
 * File: IAS-CommonLib/src/commonlib/testcase/TestSuite.h
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
#ifndef _IAS_TestSuite_H_
#define _IAS_TestSuite_H_

#include "commonlib/types.h"
#include "commonlib/memory/memory.h"
#include "commonlib/logger/logger.h"

#include "commonlib/containers/HashMapStringToPointer.h"
#include "commonlib/tools/TypeTools.h"
#include "commonlib/exception/ItemNotFoundException.h"
#include "commonlib/exception/BadUsageException.h"

#include "commonlib/memory/ma/Factory.h"

#include "TestUnit.h"
#include <list>

namespace IAS {

/*************************************************************************/
/** The TestSuite class.
 *
 */
class TestSuite {
public:

	TestSuite();
	virtual ~TestSuite() throw();

	void addTestUnit(TestUnit *pTestUnit);

	void run(const String& strCaseName="");
	void printResults(std::ostream& os);

protected:

	friend class TestUnit;

	enum Result{
		RESULT_NOT_EXECUTED,
		RESULT_OK,
		RESULT_FAILED
	};

	struct TestCase{
		TestUnit *pTestUnit;
		String strName;
		String strInfo;
		Result iResult;
		long   iTimeMS;
		long   iNewMemoryEntries;
	};

	typedef std::list<TestCase> TestCasesList;
	TestCasesList               lstTestCases;

	typedef HashMapStringToPointer<TestUnit> TestUnitsMap;
	TestUnitsMap                             hmTestUnits;

};

/*************************************************************************/
}

#endif /* _IAS_TestSuite_H_ */
