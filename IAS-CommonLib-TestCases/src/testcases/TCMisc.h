/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCMisc.h
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
#ifndef TCMISC_H_
#define TCMISC_H_


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCMisc: public TestUnit{

public:
	TCMisc(TestSuite* pTestSuite);
	virtual ~TCMisc()  throw ();

	virtual void init(TestSuite* pTestSuite);
	static TCMisc* Create(TestSuite* pTestSuite);

private:

	void caseALL();

	friend class ::IAS::Factory<TCMisc>;
	::IAS::TestRunner<TCMisc> theTestRunner;
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCMisc_H_*/
