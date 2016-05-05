/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCProcess.h
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
#ifndef TCProcess_H_
#define TCProcess_H_

#include <commonlib/commonlib.h>

#include "commonlib/testcase/TestUnit.h"

namespace IAS {
namespace TCT {

/*************************************************************************/
class TCProcess : public TestUnit{
public:
	TCProcess(TestSuite* pTestSuite);
	virtual ~TCProcess()  throw ();

	virtual void init(TestSuite* pTestSuite);

	class MyWorker : public ::IAS::SYS::Proc::Runnable{

	public:
		MyWorker(int i);
		virtual void run();

	private:
		void iterate(int i);
		int iStart;
	};

	void test1();
	void test2();
	void test3();

	
	friend class ::IAS::Factory<TCProcess>;
	::IAS::TestRunner<TCProcess> theTestRunner;
};
/*************************************************************************/

}
}

#endif /* TCTHREADS_H_ */

