/*
 * File: IAS-QSystemLib-TestCases/src/testcases/TCSubscription.h
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
#ifndef _IAS_TCT_TCSubscription_H
#define _IAS_TCT_TCSubscription_H

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCSubscription: public TestUnit{

public:

	virtual ~TCSubscription()  throw ();

protected:
	TCSubscription(TestSuite* pTestSuite);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<TCSubscription> theTestRunner;

	/************************************************************/
	struct RunnableThread : public Runnable, Thread{

		RunnableThread(TCSubscription *pMyTest):Thread(this),pMyTest(pMyTest){};
		virtual ~RunnableThread(){};

		TCSubscription *pMyTest;
	};

	struct Distributor  {
		virtual void run();
	};

	struct Publisher : public RunnableThread {
		Publisher(TCSubscription *pMyTest):RunnableThread(pMyTest){};
		virtual void run();
	};

	struct Subscriber : public RunnableThread {
		Subscriber(TCSubscription *pMyTest):RunnableThread(pMyTest){};
		virtual void run();
	};


	void caseOne();

	String strProgramName;
	String strInputFileName;

	friend class ::IAS::Factory<TCSubscription>;

	String getOutputFileName()const;


	static const String C_Subscription;

	void setStop(bool bStop=true){
		Mutex::Locker locker(mutex);
		this->bStop=bStop;
	}

	bool isStopping(){
		Mutex::Locker locker(mutex);
		return bStop;
	}

	int getNumMsgs(){
		Mutex::Locker locker(mutex);
		return iNumMsgs;
	}

private:
	String getOutputFileName();

	static URI uri;

	Mutex mutex;

	bool bStop;
	int  iNumMsgs;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
