/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/Process.cpp
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
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#include "Runnable.h"

namespace IAS {
namespace SYS {
namespace Proc {
/*************************************************************************/
Process::Process(Runnable* pRunnable):
	iPid(-1),
	bIsStarted(false),
	iFDInput(0),
	iFDOutput(1),
	iFDError(2),
	pRunnable(pRunnable){
	IAS_TRACER;
}
/*************************************************************************/
Process::~Process() throw () {
	IAS_TRACER;

	if (iFDInput != 0 && iFDInput != -1)
		close(iFDInput);

	if (iFDOutput != 1 && iFDOutput != -1)
		close(iFDOutput);

	if (iFDError != 2 && iFDError != -1)
		close(iFDError);
}
/*************************************************************************/
int Process::getPid() const {
	IAS_TRACER;

	if (iPid < 0)
		IAS_THROW(ItemNotFoundException("getPid"));

	return iPid;
}
/*************************************************************************/
void Process::start() {
	IAS_TRACER;

	if (bIsStarted)
		IAS_THROW(BadUsageException("bIsStarted"));

	switch (iPid = fork()) {

	case 0:

		try {
			startRunnable();
			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Process terminated normally, pid="<<iPid);
			exit(0);
		} catch (Exception& e) {
			IAS_LOG(LogLevel::INSTANCE.isError(),"Process terminated with exception, pid="<<iPid);
			IAS_REPORT_EXCEPTION(e);
			exit(1);
		}
		break;
	case -1:
		IAS_THROW(SystemException("fork",errno));
		break;

	default:
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Started, pid="<<iPid)
		;
		bIsStarted = true;
	}
}
/*************************************************************************/
void Process::kill(int iSignal) {
	IAS_TRACER;

	if (!bIsStarted)
		return;

	if (::kill((pid_t) iPid, iSignal) < 0)
		IAS_THROW(SystemException("kill",errno));
}
/*************************************************************************/
void Process::stop() {
	IAS_TRACER;

	if (!isRunning())
		return;

	kill(15);
	sleep(2);
	if (isRunning()) {
		kill(9);
	}
}
/*************************************************************************/
void Process::wait() {
	IAS_TRACER;

	if (!bIsStarted)
		return;

	int iStatus;
	int iRes;

	do {
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"wait, pid="<<iPid);
		iRes = waitpid(iPid, &iStatus, 0);
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"wait, pid="<<iPid<<", res="<<iRes);
	} while (iRes > 0 && (WIFSTOPPED(iStatus) || WIFCONTINUED(iStatus)));

	if (iRes < 0)
		IAS_THROW(SystemException("waitpid",errno));
}
/*************************************************************************/
bool Process::isRunning() {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"wait, pid="<<iPid);

	if (!bIsStarted)
		return false;

	int iStatus;
	int iRes;

	do {

		iRes = waitpid(iPid, &iStatus, WNOHANG);
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"wait, pid="<<iPid<<", res="<<iRes);
	} while (iRes > 0 && (WIFSTOPPED(iStatus) || WIFCONTINUED(iStatus)));

	if (iRes > 0) {
		bIsStarted = false;
		return false;
	}

	if (iRes == 0) {
		return true;
	}

	IAS_THROW(SystemException("waitpid",errno));
}
/*************************************************************************/
void Process::setupStream(int iFDStream, int& iFDNEw) {
	IAS_TRACER;

	if(iFDStream == iFDNEw)
		return;

	close(iFDStream);

	if(iFDNEw < 0)
		return;

	dup(iFDNEw);
	close(iFDNEw);
	iFDNEw=iFDStream;
}
/*************************************************************************/
void Process::startRunnable() {
	IAS_TRACER;

	setupStream(0,iFDInput);
	setupStream(1,iFDOutput);
	setupStream(2,iFDError);

	for (StringPairList::const_iterator it=lstEnvironment.begin(); it != lstEnvironment.end(); ++it) {
		if(setenv(it->first.c_str(),it->second.c_str(),1) != 0)
			IAS_THROW(SystemException("setenv():"))
	}

	pRunnable->run();
}
/*************************************************************************/
void Process::updateEnvironment(const StringPairList& lstEnvironment){
	IAS_TRACER;
	this->lstEnvironment=lstEnvironment;
}
/*************************************************************************/
void Process::setOutputStream(const String& strPath) {
	IAS_TRACER;

	int ifdNo = open(strPath.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0664);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"open="<<ifdNo);

	if (ifdNo < 0)
		IAS_THROW(SystemException("strPathOutputStream",errno));

	iFDOutput=ifdNo;
}
/*************************************************************************/
void Process::setErrorStream(const String& strPath) {
	IAS_TRACER;

	int ifdNo = open(strPath.c_str(), O_WRONLY | O_APPEND | O_CREAT, 0664);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"open="<<ifdNo);

	if (ifdNo < 0)
		IAS_THROW(SystemException("strPathOutputStream",errno));

	iFDError=ifdNo;
}
/*************************************************************************/
void Process::setInputStream(const String& strPath) {
	IAS_TRACER;

	int ifdNo = open(strPath.c_str(), O_RDONLY , 0);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"open="<<ifdNo);

	if (ifdNo < 0)
		IAS_THROW(SystemException("strPathOutputStream",errno));

	iFDInput=ifdNo;
}
/*************************************************************************/
void Process::disableOutputStream(){
	IAS_TRACER;
	iFDOutput=-1;
}
/*************************************************************************/
void Process::disableErrorStream(){
	IAS_TRACER;
	iFDError=-1;
}
/*************************************************************************/
void Process::disableInputStream(){
	IAS_TRACER;
	iFDInput=-1;
}
/*************************************************************************/
void Process::disableAllStreams(){
	IAS_TRACER;
	iFDInput=iFDOutput=iFDError=-1;
}
/*************************************************************************/
}
}
}
