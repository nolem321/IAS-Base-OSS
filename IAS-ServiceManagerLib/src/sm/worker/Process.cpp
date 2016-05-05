/*
 * File: IAS-ServiceManagerLib/src/sm/worker/Process.cpp
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
#include "Process.h"

#include <commonlib/commonlib.h>
#include "sm/mon/ProcessLockFile.h"
#include <unistd.h>

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
Process::Process(::IAS::SYS::Proc::Runnable* pRunnable):
		IAS::SYS::Proc::Process::Process(pRunnable),
		pProcessLockFile(NULL),
		bResetPGid(false){
	IAS_TRACER;
}
/*************************************************************************/
Process::~Process() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Process::resetPGid(bool bResetPGid){
	IAS_TRACER;
	this->bResetPGid=bResetPGid;
}
/*************************************************************************/
void Process::setProcessLockFile(Mon::ProcessLockFile* pProcessLockFile){
	IAS_TRACER;
	this->pProcessLockFile=pProcessLockFile;
}
/*************************************************************************/
void Process::startRunnable() {
	IAS_TRACER;

	if(bResetPGid){
		setpgid(0,0);
		setpgrp();
	}

	//TODO close unnecessary descriptors ?

	if(pProcessLockFile != NULL){
		if(!pProcessLockFile->lockNoWait())
			IAS_THROW(BadUsageException("Already locked ?"));
		pProcessLockFile->setProcessPidAndState(getpid(),Mon::ProcessLockFile::PS_STARTED);
	}

	::IAS::SYS::Proc::Process::startRunnable();
}
/*************************************************************************/
}
}
}
