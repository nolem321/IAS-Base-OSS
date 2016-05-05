/*
 * File: IAS-QSystemLib-TestCases/src/perfcases/DataObjects.h
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
#ifndef _IAS_TCT_DataObjects_H
#define _IAS_TCT_DataObjects_H


#include "commonlib/testcase/TestUnit.h"
#include <org/invenireaude/qsystem/workers/Connection.h>
#include <qs/fmt/FmtFactory.h>

namespace IAS{
namespace TCT{

class DataObjects: public TestUnit {

public:

	virtual ~DataObjects()  throw ();

protected:
	DataObjects(TestSuite* pTestSuite);

	virtual void init(TestSuite* pTestSuite);

	::IAS::TestRunner<DataObjects> theTestRunner;

	void action(const String& strFile, int iIterations);

	void caseOne();
	void caseTwo();
	void caseThree();

	IAS_DFT_FACTORY< IAS::QS::Fmt::FmtFactory >::PtrHolder ptrFmtFactory;

	IAS::Allocator* pOriginalAllocator;
	IAS_DFT_FACTORY<RegionMemoryManager>::PtrHolder      ptrMemoryManager;

	friend class ::IAS::Factory<DataObjects>;

};

} /* namespace TCT */
} /* namespace IAS */

#endif /*TCEMPTY_H_*/
