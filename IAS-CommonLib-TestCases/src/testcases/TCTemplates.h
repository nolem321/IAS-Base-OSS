/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCTemplates.h
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
#ifndef TCTemplate_H_
#define TCTemplate_H_

#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCTemplates: public TestUnit{

public:
	TCTemplates(TestSuite* pTestSuite);
	virtual ~TCTemplates()  throw ();
	
	virtual void init(TestSuite* pTestSuite);


	void caseSimple();
	void caseNested();

protected:

	void runCase(Template::Arguments& a, const Template* t, const String& strResult);

	friend class ::IAS::Factory<TCTemplates>;
	::IAS::TestRunner<TCTemplates> theTestRunner;

};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCTemplates_H_*/
