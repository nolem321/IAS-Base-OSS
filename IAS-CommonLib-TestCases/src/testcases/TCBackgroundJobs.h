/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBackgroundJobs.h
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
#ifndef TCBackgroundJobs_h_
#define TCBackgroundJobs_h_

#include "commonlib/testcase/TestUnit.h"

#include <commonlib/commonlib.h>

namespace IAS {
class TestSuite;
namespace TCT {

class TCBackgroundJobs : public TestUnit{
public:
	TCBackgroundJobs(TestSuite* pTestSuite);
	virtual ~TCBackgroundJobs() throw();

	virtual void init(TestSuite* pTestSuite);

	class SimpleBJ : public BackgroundJob{
	public:

		virtual void onStart();
		virtual void onError(::IAS::Exception& e);
		virtual void onCancel();

	protected:
		SimpleBJ(int id);
		int id;
		friend class ::IAS::Factory<SimpleBJ>;
	};

protected:
	
	void caseALL();
	::IAS::TestRunner<TCBackgroundJobs> theTestRunner;
};

}
}

#endif /* TCTHREADS_H_ */
