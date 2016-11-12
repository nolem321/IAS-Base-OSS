/*
 * File: IAS-ServiceManagerLib/src/sm/worker/StartStopHelper.cpp
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
#include "StartStopHelper.h"

#include <commonlib/commonlib.h>

#include "sm/cfg/Config.h"
#include "sm/cfg/dataobjects.h"
#include "exe/Handler.h"
#include "Process.h"
#include "sm/mon/ProcessLockFile.h"
#include <unistd.h>

#include <sm/ui/Messages.h>

using namespace ::org::invenireaude::sm::cfg;

namespace IAS {
namespace SM {
namespace Worker {

/*************************************************************************/
Mutex StartStopHelper::mutexUserMsgs;
const String& StartStopHelper::CEnvIndex("SM_INSTANCE_IDX");
/*************************************************************************/
StartStopHelper::StartStopHelper(const ::IAS::SM::Cfg::Config *pConfig) {
	IAS_TRACER;
	this->pConfig = pConfig;
	ptrExeHandler = IAS_DFT_FACTORY<Exe::Handler>::Create();
}
/*************************************************************************/
StartStopHelper::~StartStopHelper() throw () {
	IAS_TRACER;
}
/*************************************************************************/
void StartStopHelper::startInstance(const ::org::invenireaude::sm::cfg::Service* pService, int iIdx) const {
	IAS_TRACER;

	const Command* pCommand = pService->getStartCmd();
	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);

	StringPairList lstVariables;
	pConfig->buildEnvList(pService, lstVariables);

	lstVariables.push_back(std::pair<String,String>(CEnvIndex,TypeTools::IntToString(iIdx)));

	String strLogFilesBase(pConfig->getLogFilesBase(pService));

	IAS_DFT_FACTORY<SYS::Proc::Executor>::PtrHolder ptrExecutor(ptrExeHandler->createExecutor(dmResourceGrp->getExe(), pCommand));

	IAS_DFT_FACTORY<Mon::ProcessLockFile>::PtrHolder ptrProcessLockfile(
			IAS_DFT_FACTORY<Mon::ProcessLockFile>::Create(pConfig->getLckDir(),pService, iIdx));

	if (ptrProcessLockfile->isLocked()) {

		if (pConfig->isVerbose()){
			Mutex::Locker locker(mutexUserMsgs);
			pConfig->getOutput() << "Starting: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "]: ";
			pConfig->getOutput() << "skipping, process is already running." << std::endl;
		}

	} else {

		if (pConfig->isVerbose()){
			Mutex::Locker locker(mutexUserMsgs);
			pConfig->getOutput() << "Starting: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] - starting."<<std::endl;
		}

		IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<Process>::Create(ptrExecutor.getPointer()));

		ptrProcess->setOutputStream(strLogFilesBase + TypeTools::IntToString(iIdx) + ".out");
		ptrProcess->setErrorStream(strLogFilesBase + TypeTools::IntToString(iIdx) + ".err");
		ptrProcess->resetPGid(true);
		ptrProcess->setProcessLockFile(ptrProcessLockfile);
		ptrProcess->updateEnvironment(lstVariables);
		ptrProcess->start();
		if (pConfig->isVerbose()){
			pConfig->getOutput() << "Starting: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] -- started."<<std::endl;
		}
	}

	UserMessage(UI::Messages::MSGI_ServiceStarted)<<pService->getName()<<iIdx;
}

/*************************************************************************/
void StartStopHelper::kill(const ResourceGroup* dmResourceGrp, int iSignal, int iPid, const String& strInfo) const {
	IAS_TRACER;

	if (pConfig->isVerbose()) {
		Mutex::Locker locker(mutexUserMsgs);
		pConfig->getOutput() << strInfo<<", killing pid="<<iPid<<", signal="<<iSignal<<std::endl;
	}

	Ext::CommandPtr dmCommand = DataFactory::GetInstance()->createCommand();

	//TODO It is linux depended.

	dmCommand->setExe("kill");
	dmCommand->setArgs("-" + TypeTools::IntToString(iSignal));
	dmCommand->setArgs("--");
	dmCommand->setArgs(TypeTools::IntToString(iPid));
	IAS_DFT_FACTORY<SYS::Proc::Executor>::PtrHolder ptrExecutor(ptrExeHandler->createExecutor(dmResourceGrp->getExe(), dmCommand));
	IAS_DFT_FACTORY<SYS::Proc::Process>::PtrHolder ptrProcess(IAS_DFT_FACTORY<SYS::Proc::Process>::Create(ptrExecutor.getPointer()));

	ptrProcess->disableAllStreams();
	ptrProcess->start();

	usleep(100000);

}
/*************************************************************************/
void StartStopHelper::stopInstance(const ::org::invenireaude::sm::cfg::Service* pService, int iIdx, bool bKillGroups) const {

	IAS_TRACER;

	const ResourceGroup* dmResourceGrp = pConfig->getMergedServiceResourceGrps(pService);

	StringPairList lstVariables;
	pConfig->buildEnvList(pService, lstVariables);

	String strLogFilesBase(pConfig->getLogFilesBase(pService));

	IAS_DFT_FACTORY<Mon::ProcessLockFile>::PtrHolder ptrProcessLockfile(
			IAS_DFT_FACTORY<Mon::ProcessLockFile>::Create(pConfig->getLckDir(),pService, iIdx));

	if (ptrProcessLockfile->isLocked()) {

		Mon::ProcessLockFile::State      iState;
		unsigned int iPid;
		ptrProcessLockfile->getProcessPidAndState(iPid, iState);

		if(iPid == 0){
			pConfig->getOutput() << " Cannot read process PID ! ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] - will be terminated. "<<std::endl;
			return;
		}

		ptrProcessLockfile->setProcessPidAndState(iPid, Mon::ProcessLockFile::PS_ENDED);

		if (pConfig->isVerbose()) {
			Mutex::Locker locker(mutexUserMsgs);
			pConfig->getOutput() << "Stopping: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] - will be terminated. "<<std::endl;
		}

		if(pService->isSetStopCmd()){
			const Command* pCommand = pService->getStopCmd();

			IAS_DFT_FACTORY<Process>::PtrHolder ptrProcess(
					IAS_DFT_FACTORY<Process>::Create(ptrExeHandler->createExecutor(dmResourceGrp->getExe(), pCommand)));

			ptrProcess->setOutputStream(strLogFilesBase + TypeTools::IntToString(iIdx) + ".stop.out");
			ptrProcess->setErrorStream(strLogFilesBase + TypeTools::IntToString(iIdx) + ".stop.err");
			ptrProcess->resetPGid(true);
			ptrProcess->updateEnvironment(lstVariables);
			ptrProcess->start();

			usleep(3*1000000);

		}



		if (bKillGroups && ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 1, -iPid, "terminate group") ;
		}

		if (bKillGroups && ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 15, -iPid, "terminate group") ;
		}

		if (ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 1, iPid, "terminate") ;
		}

		if (ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 15, iPid, "terminate") ;
		}

		if (bKillGroups && ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 9, -iPid, "kill group") ;
		}

		if (ptrProcessLockfile->isLocked()) {
			kill(dmResourceGrp, 9, iPid, "kill") ;
		}


		if (pConfig->isVerbose()) {
			Mutex::Locker locker(mutexUserMsgs);
			pConfig->getOutput() << "Stopping: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] - terminated. "<<std::endl;
		}

		UserMessage(UI::Messages::MSGI_ServiceStopped)<<pService->getName()<<iIdx;

	} else {

		ptrProcessLockfile->setProcessPidAndState(0, Mon::ProcessLockFile::PS_ENDED);

		if (pConfig->isVerbose()){
			Mutex::Locker locker(mutexUserMsgs);
			pConfig->getOutput() << "Stopping: ";
			pConfig->getOutput().width(30);
			pConfig->getOutput()<<pService->getName() << "[" << iIdx << "] -- not running."<<std::endl;
		}


		UserMessage(UI::Messages::MSGI_ServiceNotRunning)<<pService->getName()<<iIdx;
	}

	pConfig->getOutput().flush();
}
/*************************************************************************/

}
}
}
