/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCStorage.h
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
#ifndef _IAS_TCT_TCStorage_H
#define _IAS_TCT_TCStorage_H


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCStorage: public TestUnit{

public:

	virtual ~TCStorage()  throw ();

protected:
	TCStorage(TestSuite* pTestSuite);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<TCStorage> theTestRunner;

	void caseOne();
	void caseTwo();
	void caseThree();

	String strProgramName;
	String strInputFileName;

	friend class ::IAS::Factory<TCStorage>;

	String getOutputFileName()const;

private:
	String getOutputFileName();
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
