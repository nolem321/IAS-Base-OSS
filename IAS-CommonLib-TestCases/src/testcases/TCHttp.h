/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCHttp.h
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
#ifndef TCHttp_H_
#define TCHttp_H_


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCHttp: public TestUnit{

public:
	TCHttp(TestSuite* pTestSuite);
	virtual ~TCHttp()  throw ();

	virtual void init(TestSuite* pTestSuite);
	static TCHttp* Create(TestSuite* pTestSuite);

private:

	void caseRequest();
	void caseResponse();
	void caseChunked();
	void caseKnownLength();
	friend class ::IAS::Factory<TCHttp>;
	::IAS::TestRunner<TCHttp> theTestRunner;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCHttp_H_*/
