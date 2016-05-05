/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCFolderBasedContent.h
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
#ifndef TCFolderBasedContent_H_
#define TCFolderBasedContent_H_

#include "commonlib/testcase/TestUnit.h"
#include <commonlib/commonlib.h>

namespace IAS{
namespace TCT{

class TCFolderBasedContent: public TestUnit{

public:
	TCFolderBasedContent(TestSuite* pTestSuite);
	virtual ~TCFolderBasedContent()  throw ();
	
protected:

	struct Content{
		Content(const String& i);
		virtual ~Content(){};
		String i;
	};

	typedef FolderBasedContent<Content,'.'> FoldersType;

	void printFolder(FoldersType* pFolder, const String& strPrefix="");

	virtual void test01();
	virtual void test02();

	friend class ::IAS::Factory<TCFolderBasedContent>;
	::IAS::TestRunner<TCFolderBasedContent> theTestRunner;
};


} /* namespace TCT */
} /* namespace IAS */


#endif /*TCPROPERTIES_H_*/
