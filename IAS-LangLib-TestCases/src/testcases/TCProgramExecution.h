/*
 * File: IAS-LangLib-TestCases/src/testcases/TCProgramExecution.h
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
#ifndef _IAS_TCT_TCProgramExecution_H
#define _IAS_TCT_TCProgramExecution_H


#include "commonlib/testcase/TestUnit.h"

namespace IAS{
namespace TCT{

class TCProgramExecution: public TestUnit{

public:

	virtual ~TCProgramExecution()  throw ();

protected:
	TCProgramExecution(TestSuite* pTestSuite,
					   const String& strProgramName,
					   const String& strInputFileName);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<TCProgramExecution> theTestRunner;

	void caseOne();

	String strProgramName;
	String strInputFileName;

	friend class ::IAS::Factory<TCProgramExecution>;

	String getOutputFileName()const;

private:
	String getOutputFileName();
};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
