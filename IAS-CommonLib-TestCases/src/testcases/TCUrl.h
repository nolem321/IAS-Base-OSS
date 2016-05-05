/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCUrl.h
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
#ifndef TCUrl_H_
#define TCUrl_H_


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCUrl: public TestUnit{

public:
	TCUrl(TestSuite* pTestSuite);
	virtual ~TCUrl()  throw ();

	virtual void init(TestSuite* pTestSuite);
	static TCUrl* Create(TestSuite* pTestSuite);

private:

	void testUrl(const String& strUrl,
				 const String& strProtocol,
				 const String& strDomain,
				 unsigned int iPort,
				 const String& strPath);

	void caseALL();

	friend class ::IAS::Factory<TCUrl>;
	::IAS::TestRunner<TCUrl> theTestRunner;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCUrl_H_*/
