/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCFileSystem.cpp
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

#include "TCFileSystem.h"

#include "commonlib/sys/fs/DirectoryReader.h"

namespace IAS {
using namespace SYS::FS;
namespace TCT {

/*************************************************************************/

TCFileSystem::TCFileSystem(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);
}
/*************************************************************************/

TCFileSystem::~TCFileSystem() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void TCFileSystem::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCFileSystem::caseALL);
	TestUnit::init("TCFileSystem",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCFileSystem::caseALL(){
	IAS_TRACER;

	IAS_DFT_FACTORY<DirectoryReader>::PtrHolder ptrReader(IAS_DFT_FACTORY<DirectoryReader>::Create("/tmp"));

	ptrReader->read();

	const DirectoryReader::EntriesList& lstEntries = ptrReader->getEntries();

	for (DirectoryReader::EntriesList::const_iterator it = lstEntries.begin(); it != lstEntries.end(); it++) {

		std::cout << (unsigned char) (*it)->iType << ":" << (*it)->strFile << std::endl;
	}

}
/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
