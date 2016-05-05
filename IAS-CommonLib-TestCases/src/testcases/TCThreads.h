/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCThreads.h
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
#ifndef TCTHREADS_H_
#define TCTHREADS_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS {
namespace TCT {

class TCThreads : public TestUnit{
public:
	TCThreads(TestSuite* pTestSuite);
	virtual ~TCThreads()  throw ();

	virtual void init(TestSuite* pTestSuite);

	struct Object {
		Object();
		virtual ~Object();

		String strInfo;
	};

	class MyThread : public IAS::Runnable{

	public:
		MyThread(int i);
		virtual void run();

	private:
		void iterate(int i);
		int iStart;

		IAS_DFT_FACTORY<TCThreads::Object>::ThreadSpecificPtr ptrObject;
	};

	void caseALL();

	friend class ::IAS::Factory<TCThreads>;
	::IAS::TestRunner<TCThreads> theTestRunner;
};

}

}

#endif /* TCTHREADS_H_ */
