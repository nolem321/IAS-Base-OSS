/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCFileLock.cpp
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

#include "commonlib/sys/fs/FileLock.h"

#include "TCFileLock.h"
#include <unistd.h>

namespace IAS{
using namespace SYS;
using namespace SYS::FS;
namespace TCT{

/*************************************************************************/
	
TCFileLock::TCFileLock(TestSuite* pTestSuite):theTestRunner(this){
	IAS_TRACER;
	init(pTestSuite);
}

/*************************************************************************/

TCFileLock::~TCFileLock() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCFileLock::init(TestSuite* pTestSuite){	
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCFileLock::caseALL);
	TestUnit::init("TCFileLock",&theTestRunner,pTestSuite);
}
/*************************************************************************/
void TCFileLock::child(){
	IAS_TRACER;
	usleep(1000000);

	IAS_DFT_FACTORY<FileLock>::PtrHolder ptrFileLock(IAS_DFT_FACTORY<FileLock>::Create("/var/tmp/ak.lock"));

	ptrFileLock->lock();
	sleep(1);
	ptrFileLock->writeContent("Love my parents.");
	for(int i=0; i< 5; i++ ){
		std::cout<<"Beep:"<<i<<std::endl;
		usleep(100000);
	}

	//execl("/usr/bin/sudo","/usr/bin/sudo","-u","test","/bin/sleep","5",NULL);
	execl("/bin/sleep","/bin/sleep","5",NULL);
	return;
	IAS_THROW(SystemException("exec",errno));
}
/*************************************************************************/
void TCFileLock::parent(){
	IAS_TRACER;

	{
		IAS_DFT_FACTORY<FileLock>::PtrHolder ptrFileLock(IAS_DFT_FACTORY<FileLock>::Create("/var/tmp/ak.lock"));
		ptrFileLock->writeContent("");
	}

	int iNum = 100;

	IAS_DFT_FACTORY<FileLock>::PtrHoldersCollection phcFileLocks;

	for(int i=0; i<iNum; i++){
		phcFileLocks.addPointer(IAS_DFT_FACTORY<FileLock>::Create("/var/tmp/ak.lock"));
	}

	bool bStop = false;
	while(!bStop){
		Timestamp ts;
		String strInfo;
		bool bHasLock;

	    struct timeval tvData;
		gettimeofday(&tvData,NULL);
	    long iTimeStartedMS=tvData.tv_sec*1000+tvData.tv_usec/1000;

		for(IAS_DFT_FACTORY<FileLock>::PtrHoldersCollection::iterator it=phcFileLocks.begin();
				it != phcFileLocks.end(); it++){

			if(strInfo.empty())
				(*it)->readContent(strInfo);
			bHasLock = (*it)->isLocked();
		}

		gettimeofday(&tvData,NULL);
	    long iTimeMS=tvData.tv_sec*1000+tvData.tv_usec/1000 - iTimeStartedMS;

		std::cout<<ts.toString()<<"  "<<bHasLock<<":["<<strInfo<<"], time="<<iTimeMS<<std::endl;
		usleep(300000);

		bStop = !bHasLock && strInfo.length() > 0;
	}

	return;
}
/*************************************************************************/
void TCFileLock::caseALL(){
	
	IAS_TRACER;

	try{
		
		switch(fork()){
			case -1:
				IAS_THROW(SystemException("fork"));
				break;
			case 0:
				child();
				exit(1);
				break;
			default:
				parent();
				break;
		}
	}catch(Exception& e){
		IAS_REPORT_EXCEPTION(e);
	}
}

/*************************************************************************/

} /* namespace TCT */
} /* namespace IAS */
