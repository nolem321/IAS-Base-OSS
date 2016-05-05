/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCTime.h
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
#ifndef TCTIME_H_
#define TCTIME_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCTime: public TestUnit{

public:
	TCTime(TestSuite* pTestSuite);
	virtual ~TCTime()  throw ();
	
	virtual void init(TestSuite* pTestSuite);
	void caseTimesample();

	void caseTimestampConversionsSimple();
	void caseTimestampConversionsZones();

	void caseTime();
	void caseDate();

protected:

	 void testTimestampConversion(const String& strInput,
			 	 	 	 	 	  const String& strFormat);

	 void testTimestampConversion(const String& strInput,
				 	 	 	 	  const String& strIFormat,
				 	 	 	 	  const String& strOutput,
				 	 	 	 	  const String& strOFormat);

	friend class ::IAS::Factory<TCTime>;
	::IAS::TestRunner<TCTime> theTestRunner;

};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCTime_H_*/
