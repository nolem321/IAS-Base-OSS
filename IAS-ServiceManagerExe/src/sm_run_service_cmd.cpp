/*
 * File: IAS-ServiceManagerExe/src/sm_run_service_cmd.cpp
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

#include "sm/cmdline/StartParameters.h"
#include "sm/api/ServiceManager.h"
#include <unistd.h>

using namespace IAS;
using namespace IAS::SM;

int main(int argc, char* argv[]) {
	IAS_TRACER;
	IAS::Logger::GetInstance();


	try {

		if (argc != 2)
			return 1;

		IAS_DFT_FACTORY<API::ServiceManager>::PtrHolder ptrServiceManager(IAS_DFT_FACTORY<API::ServiceManager>::Create());
		ptrServiceManager->runServiceCommand(argv[1], true);


	} catch (IAS::SystemException& e) {
		std::cerr << "System Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (IAS::Exception& e) {
		std::cerr << "Exception:\n";
		e.printToStream(std::cerr);
		std::cerr << "\n";
	} catch (...) {
		std::cerr << "Unhandled exception !\n";
	}

	if(LogLevel::INSTANCE.bIsInfo){
		IAS::MemoryManager::GetInstance()->printToStream(std::cout);
		IAS::TracerStats::GetInstance()->printToStream(std::cout);
	}
}
