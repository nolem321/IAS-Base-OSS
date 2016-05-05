/*
 * File: IAS-CommonLib/src/commonlib/threads/BackgroundJobsExecutor.cpp
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
#include "BackgroundJobsExecutor.h"

#include "BackgroundJob.h"
#include "BackgroundJobEntry.h"
#include "BackgroundJobThread.h"

#include "BackgroundJobsQueue.h"

namespace IAS {

/*************************************************************************/
BackgroundJobsExecutor::BackgroundJobsExecutor(int iNumThreads, int iQueueSize):
	iNumThreads(iNumThreads){
	IAS_TRACER;
	init(iQueueSize);
}
/*************************************************************************/
BackgroundJobsExecutor::~BackgroundJobsExecutor() throw(){
	IAS_TRACER;

	if(bCompleteJobsOnDelete){

		for(int iIdx=0; iIdx < iNumThreads; iIdx++){
			IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"Setting end of work BJT:"<<iIdx);
			tabThreads[iIdx]->setEndOfWorkState();
		}

		ptrQueue->close();

		for(int iIdx=0; iIdx < iNumThreads; iIdx++){
			IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"Waiting for BJT:"<<iIdx);
			tabThreads[iIdx]->join();
		}
	}

	try{
		tabThreads.clear();
	}catch(...){}
}
/*************************************************************************/
void BackgroundJobsExecutor::setCompleteJobsOnDelete(bool bCompleteJobsOnDelete){
	IAS_TRACER;
	this->bCompleteJobsOnDelete=bCompleteJobsOnDelete;
}
/*************************************************************************/
void BackgroundJobsExecutor::enqueue(BackgroundJob *pJob){
	IAS_TRACER;

	IAS_CHECK_IF_VALID(pJob);
	IAS_DFT_FACTORY<BackgroundJobEntry>::PtrHolder ptrEntry(IAS_DFT_FACTORY<BackgroundJobEntry>::Create(pJob));

	ptrQueue->addEntry(ptrEntry.pass());
}
/*************************************************************************/
void BackgroundJobsExecutor::init(int iQueueSize){
	IAS_TRACER;

	ptrQueue = IAS_DFT_FACTORY<BackgroundJobsQueue>::Create(iQueueSize);

	tabThreads.clear();
	for(int iIdx=0; iIdx<iNumThreads; iIdx++){
		BackgroundJobThread* p=IAS_DFT_FACTORY<BackgroundJobThread>::Create(ptrQueue.getPointer());
		tabThreads.push_back(p);
	}

	bCompleteJobsOnDelete=false;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Starting threads: "<<tabThreads.size() <<", iNumThreads="<<iNumThreads);

	for(ThreadsTab::iterator it=tabThreads.begin();
		it != tabThreads.end();
		it++){
		(*it)->start();
	}
}
/*************************************************************************/
}
