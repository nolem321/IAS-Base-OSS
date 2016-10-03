/*
 * File: IAS-CommonLib-TestCases/src/commonlib-testcases.cpp
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

#include "commonlib/testcase/TestSuite.h"
#include "commonlib/testcase/TestUnit.h"

#include "testcases/TCEmpty.h"
#include "testcases/TCProperties.h"
#include "testcases/TCTime.h"
#include "testcases/TCMisc.h"
#include "testcases/TCThreads.h"
#include "testcases/TCPtrHoldersCollection.h"
#include "testcases/TCCache.h"
#include "testcases/TCBackgroundJobs.h"
#include "testcases/TCBitMap.h"
#include "testcases/TCCache.h"
#include "testcases/TCFileLock.h"
#include "testcases/TCFileSystem.h"
#include "testcases/TCHashMapOfPointers.h"
#include "testcases/TCFolderBasedContent.h"
#include "testcases/TCHashMapStrings.h"
#include "testcases/TCMisc.h"
#include "testcases/TCProcess.h"
#include "testcases/TCProcessList.h"

#include "testcases/TCRefCountingPtr.h"
#include "testcases/TCSemaphore.h"
#include "testcases/TCShareable.h"
#include "testcases/TCSimpleMemoryManager.h"
#include "testcases/TCPowerOfTwoMemoryManager.h"
#include "testcases/TCStreamMemoryBuffer.h"
#include "testcases/TCRegionMemoryManager.h"
#include "testcases/TCUrl.h"
#include "testcases/TCBlockIOBuffer.h"
#include "testcases/TCSerializationHelper.h"
#include "testcases/TCSockets.h"
#include "testcases/TCBucketCache.h"
#include "testcases/TCHttp.h"
#include "testcases/TCTemplates.h"

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

		if(1) {

			//LogLevel::INSTANCE.bIsInfo=LogLevel::INSTANCE.bIsDetailedInfo=true;
			//LogLevel::INSTANCE.bIsProfile=true;
			//LogLevel::INSTANCE.bIsMemory=true;

			//IAS_DFT_FACTORY<TCStreamMemoryBuffer>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCMisc>::Create(ptrSuite.getPointer());

		} else {
/*
 */
			IAS_DFT_FACTORY<TCBitMap>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCEmpty>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCBackgroundJobs>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCCache>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCFileLock>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCFileSystem>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCFolderBasedContent>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCHashMapOfPointers>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCMisc>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCProcess>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCProcessList>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCHashMapStrings>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCProperties>::Create(ptrSuite.getPointer());
/*
			IAS_DFT_FACTORY<TCPtrHoldersCollection>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCRefCountingPtr>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCSemaphore>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCThreads>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCTime>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCShareable>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCSimpleMemoryManager>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCPowerOfTwoMemoryManager>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCRegionMemoryManager>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCUrl>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCStreamMemoryBuffer>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCBlockIOBuffer>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCSerializationHelper>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCSockets>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCBucketCache>::Create(ptrSuite.getPointer());
			IAS_DFT_FACTORY<TCHttp>::Create(ptrSuite.getPointer());
*/
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

	std::cout << "ALL:\n";
	IAS::MemoryManager::GetInstance()->printToStream(std::cout);
	std::cout << "Tracer:\n";
	//IAS::TracerStats::GetInstance()->printToStream(std::cout);
	std::cout << "Ending\n";
}
