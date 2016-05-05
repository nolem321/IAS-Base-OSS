/*
 * File: IAS-QSystemLib-TestCases/src/ias_qs_testcases.cpp
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

#include <dm/Impl/MemoryManager.h>

#include "commonlib/testcase/TestSuite.h"
#include "commonlib/testcase/TestUnit.h"

#include "testcases/TCEventCounter.h"
#include "testcases/TCConnect.h"
#include "testcases/TCStorage.h"
#include "testcases/TCSubscription.h"

using namespace IAS;
using namespace TCT;

char t[5] = { 0, 1, 3, 5, 6 };


int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();

	std::cout << "Starting\n";

	try {

		IAS_DFT_FACTORY<TestSuite>::PtrHolder ptrSuite;
		ptrSuite = IAS_DFT_FACTORY<TestSuite>::Create();

		std::cerr<<"suite="<<(void*)ptrSuite.getPointer()<<std::endl;

		IAS_DFT_FACTORY<TCEventCounter>::Create(ptrSuite.getPointer());

		if(0){
			IAS_DFT_FACTORY<TCConnect>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCStorage>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCSubscription>::Create(ptrSuite.getPointer());
		}

		ptrSuite->run(argc == 1 ? "" : argv[1]);
		ptrSuite->printResults(std::cout);

	} catch (IAS::SystemException& e) {
		std::cerr << "System Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (IAS::Exception& e) {
		std::cerr << "Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (...) {
		std::cerr << "Unknown exception !\n";
	}

	std::cout<<"Ending\n";

	std::cerr<<"DM:\n";
	//IAS::DM::Impl::MemoryManager::PrintToStream(std::cerr, false);
	//std::cout << "ALL:\n";
	//IAS::MemoryManager::GetInstance()->printToStream(std::cerr);
	std::cerr << "Tracer:\n";
	IAS::TracerStats::GetInstance()->printToStream(std::cerr);
	std::cerr << "Ending\n";
}
