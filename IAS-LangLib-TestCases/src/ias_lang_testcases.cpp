/*
 * File: IAS-LangLib-TestCases/src/ias_lang_testcases.cpp
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

#include "testcases/TCProgramExecution.h"
#include "testcases/TCProgramPrinting.h"
#include "testcases/TCTypePrinting.h"
using namespace IAS;
using namespace TCT;

char t[5] = { 0, 1, 3, 5, 6 };

#define IAS_TEST_EXE(a,b) { IAS_DFT_FACTORY<TCProgramExecution>::Create(ptrSuite.getPointer(), a, b); }
#define IAS_TEST_PRT(a)   { IAS_DFT_FACTORY<TCProgramPrinting>::Create(ptrSuite.getPointer(), a); }
#define IAS_TEST_TYP(a,b,c)   { IAS_DFT_FACTORY<TCTypePrinting>::Create(ptrSuite.getPointer(), a,b,c); }

int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();

	std::cout << "Starting\n";

	try {

		IAS_DFT_FACTORY<TestSuite>::PtrHolder ptrSuite;
		ptrSuite = IAS_DFT_FACTORY<TestSuite>::Create();

		 //std::cerr<<"suite="<<(void*)ptrSuite.getPointer()<<std::endl;


		IAS_TEST_TYP("com::examples::types::types01","ExampleType", "http://www.examples.org/types");
		IAS_TEST_TYP("com::examples::types::types01","SubExampleType", "http://www.examples.org/types");
		IAS_TEST_TYP("com::examples::types::types01","SubAddress", "http://www.examples.org/types");

	 	IAS_TEST_PRT("com::examples::types::types01");
	 	IAS_TEST_PRT("com::examples::basic::anytype");
	 	IAS_TEST_PRT("com::examples::basic::fileops");
	 	IAS_TEST_PRT("com::examples::basic::assign01");
	 	IAS_TEST_PRT("com::examples::basic::tabs01");
	 	IAS_TEST_PRT("com::examples::basic::loop01");
	 	IAS_TEST_PRT("com::examples::basic::loop02");
	 	IAS_TEST_PRT("com::examples::basic::loop03");
	 	IAS_TEST_PRT("com::examples::basic::compute01");
	 	IAS_TEST_PRT("com::examples::basic::catch01");
	 	IAS_TEST_PRT("com::examples::basic::catch02");
	 	IAS_TEST_PRT("com::examples::basic::datetime");
	 	IAS_TEST_PRT("com::examples::basic::withsingle");
	 	IAS_TEST_PRT("com::examples::basic::cast");
		IAS_TEST_PRT("com::examples::basic::newfuncalls");

		IAS_TEST_EXE("com::examples::types::types01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::anytype", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::fileops", "customer.xml");
	 	IAS_TEST_EXE("com::examples::basic::assign01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::tabs01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::loop01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::loop02", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::loop03", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::datetime", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::compute01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::catch01", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::catch02", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::catch03", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::withsingle", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::cast", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::sort", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::merge", "customer.xml");
		IAS_TEST_EXE("com::examples::basic::newfuncalls", "customer.xml");

		IAS_TEST_EXE("com::examples::basic::inlinetypes", "customer.xml");

		/**/






		/* old stuff for fun : IAS_TEST_EXE("com::examples::test", "customer.xml");*/

		//ptrSuite->run(argc == 1 ? "" : argv[1]);
		ptrSuite->run("com::examples::basic::merge");
		//ptrSuite->run("");

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

	std::cerr << "Ending\n";
}
