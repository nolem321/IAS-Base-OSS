/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/Put.h
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
#ifndef _IAS_TCT_Put_H
#define _IAS_TCT_Put_H


#include "commonlib/testcase/TestUnit.h"
#include <org/invenireaude/qsystem/workers/Connection.h>

#include "Base.h"

namespace IAS{
namespace TCT{

class Put: public TestUnit, Base {

public:

	virtual ~Put()  throw ();

protected:
	Put(TestSuite* pTestSuite);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<Put> theTestRunner;

	struct Variant{
		int iMsgSize;
		int iNumMsgs;

		bool bOnlyCreateEmpty;
		bool bMockContent;
		bool bBigAttrs;
		bool bSend;
	};

	void action(const Variant& v);
	void iterator(const String& strName, Variant& v);

	void caseEmpty();
	void caseZero();
	void caseOne();
	void caseTwo();
	void caseThree();

	String strProgramName;
	String strInputFileName;

	friend class ::IAS::Factory<Put>;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
