/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCPtrHoldersCollection.h
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
#ifndef TCPtrHoldersCollection_H_
#define TCPtrHoldersCollection_H_


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCPtrHoldersCollection: public TestUnit{

public:
	TCPtrHoldersCollection(TestSuite* pTestSuite);
	virtual ~TCPtrHoldersCollection()  throw ();

private:

	virtual void init(TestSuite* pTestSuite);

	class MyTestObject{
			public:
			virtual ~MyTestObject() throw();
			int id;

			protected:
			MyTestObject(int id=-1):id(id){std::cout<<"New test object:"<<id<<"\n";};
			friend class ::IAS::Factory<MyTestObject>;
		};


	
	void caseALL();

	friend class ::IAS::Factory<TCPtrHoldersCollection>;
	::IAS::TestRunner<TCPtrHoldersCollection> theTestRunner;
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCPtrHoldersCollection_H_*/
