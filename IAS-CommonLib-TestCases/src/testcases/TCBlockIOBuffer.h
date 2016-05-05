/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBlockIOBuffer.h
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
#ifndef TCBlockIOBuffer_H_
#define TCBlockIOBuffer_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCBlockIOBuffer: public TestUnit{

public:
	TCBlockIOBuffer(TestSuite* pTestSuite);
	virtual ~TCBlockIOBuffer()  throw ();
	
	virtual void init(TestSuite* pTestSuite);

	void case01();
	void case02();
	void case03();
	void case04();

	friend class ::IAS::Factory<TCBlockIOBuffer>;
	::IAS::TestRunner<TCBlockIOBuffer> theTestRunner;
};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCBlockIOBuffer_H_*/
