/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCRegionMemoryManager.h
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
#ifndef TCRegionMemoryManager_H_
#define TCRegionMemoryManager_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCRegionMemoryManager: public TestUnit{

public:
	TCRegionMemoryManager(TestSuite* pTestSuite);
	virtual ~TCRegionMemoryManager()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

	void caseALL();

	struct Object{


			Object(int iValue):iValue(iValue){
				std::cerr<<"Creating object"<<iValue<<" at:"<<(void*)this<<std::endl;
			}

			virtual ~Object(){
				std::cerr<<"Deleting object at:"<<(void*)this<<std::endl;
			}

			int iValue;
			int iValue2;
			int iValue3;
		};


	friend class ::IAS::Factory<TCRegionMemoryManager>;
	::IAS::TestRunner<TCRegionMemoryManager> theTestRunner;

};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCRegionMemoryManager_H_*/
