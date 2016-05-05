/*
 * File: IAS-DataModelLib-TestCases/src/ias_dm_tests.cpp
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
#include <commonlib/commonlib.h>
#include <dm/Impl/MemoryManager.h>

#include "tc/dm/Customer01.h"
#include "tc/dm/CustomerJSON.h"
#include "tc/dm/CustomerXML.h"
#include "tc/dm/CustomerXPathWrapper.h"
#include "tc/dm/CustomerXSD.h"

using namespace IAS;
using namespace TC;
using namespace TC::DM;

int main(int argc, char* argv[]){

	IAS_TRACER;
	IAS::Logger::GetInstance();

	std::cout<<"Starting\n";
	try{

		IAS_DFT_FACTORY<TestSuite>::PtrHolder ptrSuite;
		ptrSuite = IAS_DFT_FACTORY<TestSuite>::Create();

		std::cerr<<"suite="<<(void*)ptrSuite.getPointer()<<std::endl;


		//IAS_DFT_FACTORY<Customer01>::Create(ptrSuite.getPointer());
		//IAS_DFT_FACTORY<CustomerXSD>::Create(ptrSuite.getPointer());
		IAS_DFT_FACTORY<CustomerXML>::Create(ptrSuite.getPointer());
		//IAS_DFT_FACTORY<CustomerJSON>::Create(ptrSuite.getPointer());
		//IAS_DFT_FACTORY<CustomerXPathWrapper>::Create(ptrSuite.getPointer());
		ptrSuite->run(argc == 1 ? "" : argv[1]);
		ptrSuite->printResults(std::cout);


	}catch(IAS::Exception& e){
		std::cout<<"Exception:\n";
		e.printToStream(std::cout);
		std::cout<<"\n";
	}catch(...){
		std::cout<<"Ending with exception.\n";
	}
	std::cout<<"Ending\n";
	std::cout<<"DM:\n";
	IAS::DM::Impl::MemoryManager::PrintToStream(std::cout, false);
	std::cout << "ALL:\n";
	//IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout << "Tracer:\n";
	IAS::TracerStats::GetInstance()->printToStream(std::cout);
	std::cout << "Ending\n";
}
