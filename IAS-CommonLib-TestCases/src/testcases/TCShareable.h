/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCShareable.h
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
#ifndef TCShareable_H_
#define TCShareable_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCShareable: public TestUnit{

public:
	TCShareable(TestSuite* pTestSuite);
	virtual ~TCShareable()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

	void caseALL();

	friend class ::IAS::Factory<TCShareable>;
	::IAS::TestRunner<TCShareable> theTestRunner;

	struct Object{

		Object():iValue(0){
			strValue[0]=0;
			std::cerr<<"Creating object at:"<<(void*)this<<std::endl;
		}

		~Object(){
			std::cerr<<"Deleting object at:"<<(void*)this<<std::endl;
		}

		int iValue;
		char strValue[256];
	};

	String strObjectName;

	void testChild(const String& s);

};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCShareable_H_*/
