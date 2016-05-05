/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCPowerOfTwoMemoryManager.h
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
#ifndef TCPowerOfTwoMemoryManager_H_
#define TCPowerOfTwoMemoryManager_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCPowerOfTwoMemoryManager: public TestUnit{

public:
	TCPowerOfTwoMemoryManager(TestSuite* pTestSuite);
	virtual ~TCPowerOfTwoMemoryManager()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

	void case01logic(int iSize, int iNumObjects);
	void case01();
	void case02();

	struct Object{


			Object(int iValue):iValue(iValue){
				//std::cerr<<"Creating object"<<iValue<<" at:"<<(void*)this<<std::endl;
			}

			virtual ~Object(){
				//std::cerr<<"Deleting object at:"<<(void*)this<<std::endl;
			}

			int iValue;
			char tValue2[31];
		};


	friend class ::IAS::Factory<TCPowerOfTwoMemoryManager>;
	::IAS::TestRunner<TCPowerOfTwoMemoryManager> theTestRunner;

	static Allocator *TheAllocator;

	static Allocator *GetAllocator(){ return TheAllocator; };
};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCPowerOfTwoMemoryManager_H_*/
