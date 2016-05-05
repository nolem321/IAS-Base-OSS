/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCCache.cpp
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
#include "commonlib/commonlib.h"
#include "TCCache.h"

#include<stdlib.h>

namespace IAS {

namespace TCT {

TCCache::TCCache(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);

}

TCCache::~TCCache() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCCache::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCCache::caseALL);
	TestUnit::init("TCCache",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCCache::caseALL() {
	IAS_TRACER;

	StrDupCache cache;

	int iNumEntries = 10;

	for(int i=0;i<iNumEntries;i++){
		StringStream ss;
		ss<<i;
		cache.getResource(ss.str());
	}

	cache.dumpEntries(std::cout);

	for(int i=0;i<iNumEntries;i++){
		StringStream ss;
		ss<<i;
		Resource *pResource = cache.getResource(ss.str());
		std::cout<<"i="<<i<<":"<<((void*)pResource)<<"\n";
	}

	for(int i=iNumEntries+1;i<2*iNumEntries;i++){
			StringStream ss;
			ss<<i;
			cache.getResource(ss.str());
		}

	cache.dumpEntries(std::cout);


	for(int i=0;i<iNumEntries/2;i++){
		StringStream ss;
		ss<<i;
		cache.getResource(ss.str());
	}
}

/*************************************************************************/
TCCache::Resource *TCCache::StrDupCache::retrieve(const String& key){
	IAS_TRACER;

	return IAS_DFT_FACTORY<Resource>::Create(key);
}
/*************************************************************************/

}
}
