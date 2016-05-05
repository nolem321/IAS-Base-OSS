/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCSemaphore.h
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
#ifndef TCSemaphore_H_
#define TCSemaphore_H_

#include "commonlib/testcase/TestUnit.h"

#include <commonlib/commonlib.h>
#include <commonlib/sys/ipc/ipc.h>

namespace IAS {
namespace TCT {

class TCSemaphore : public TestUnit{
public:
	TCSemaphore(TestSuite* pTestSuite);
	virtual ~TCSemaphore()  throw ();

	virtual void init(TestSuite* pTestSuite);

	class Worker : public IAS::Runnable{

	public:
		Worker();
		virtual void runImpl();
		virtual void run();
		void init(const String& strPath);

		IPC::SemaphoreArray::Descriptor     aSemaphoreDesc;
		IPC::SharedMemory::Descriptor  aSharedMemoryDesc;

		volatile static bool bStop;

	};

	void caseALL();

	friend class ::IAS::Factory<TCSemaphore>;
	::IAS::TestRunner<TCSemaphore> theTestRunner;
	
};

}

}

#endif /* TCTHREADS_H_ */
