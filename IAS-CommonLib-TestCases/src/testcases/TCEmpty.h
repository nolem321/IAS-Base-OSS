/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCEmpty.h
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
#ifndef _IAS_TCT_TCEmpty_H
#define _IAS_TCT_TCEmpty_H


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCEmpty: public TestUnit{

public:
	TCEmpty(TestSuite* pTestSuite);
	virtual ~TCEmpty()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

private:
	void iterate(int i);
	
	::IAS::TestRunner<TCEmpty> theTestRunner;

	void caseALL();
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
