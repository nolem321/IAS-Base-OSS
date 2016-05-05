/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCHashMapOfPointers.h
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
#ifndef TCHashMapOfPointers_H_
#define TCHashMapOfPointers_H_


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCHashMapOfPointers: public TestUnit{

public:
	TCHashMapOfPointers(TestSuite* pTestSuite);
	virtual ~TCHashMapOfPointers()  throw ();

protected:
	virtual void init(TestSuite* pTestSuite);

private:

	class MyTestObject{
		public:

		virtual ~MyTestObject() throw();

		int id;

		static int TheCount;

		protected:

		MyTestObject(int id)throw();

		friend class ::IAS::Factory<MyTestObject>;
	};
	
	void caseALL();

	
	friend class ::IAS::Factory<TCHashMapOfPointers>;
	::IAS::TestRunner<TCHashMapOfPointers> theTestRunner;
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCHashMapOfPointers_H_*/
