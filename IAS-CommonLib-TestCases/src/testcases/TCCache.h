/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCCache.h
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
#ifndef TCCache_H_
#define TCCache_H_

#include "commonlib/commonlib.h"

#include "commonlib/testcase/TestUnit.h"

namespace IAS {
namespace TCT {

class TCCache : public TestUnit{
public:

	virtual ~TCCache()  throw ();

	virtual void init(TestSuite* pTestSuite);

	class Resource{
		public:

		 virtual ~Resource(){std::cout<<"Deleted:"<<s<<"\n";};
		 String& getInfo(){return s;};

		protected:
		 Resource(const String& s):s(s){std::cout<<"Resource created:"<<s<<"\n";};
		 String s;
		 friend class ::IAS::Factory<Resource>;
	};

	class StrDupCache: public Cache::SimpleCacheSynchronized<Resource,String>{
	 protected:

		virtual Resource* retrieve(const String& key);
	};

	protected:

	TCCache(TestSuite* pTestSuite);
	void caseALL();

	friend class ::IAS::Factory<TCCache>;
	::IAS::TestRunner<TCCache> theTestRunner;
};

}
}

#endif /* TCCache_H_ */
