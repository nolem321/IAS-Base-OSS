/*
 * File: IAS-ServiceManagerLib/src/sm/mon/ProcessLockFile.cpp
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
#include "ProcessLockFile.h"

#include <commonlib/commonlib.h>

namespace IAS {
namespace SM {
namespace Mon {

/*************************************************************************/
ProcessLockFile::ProcessLockFile(const String& strLockDir,
							     const ::org::invenireaude::sm::cfg::Service* pService,
		   	   	   	   	   	     int iInstanceIdx):
 SYS::FS::FileLock(strLockDir+"/"+getFileName(pService,iInstanceIdx)){

	IAS_TRACER;
	IAS_CHECK_IF_VALID(pService);
}
/*************************************************************************/
ProcessLockFile::~ProcessLockFile() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void ProcessLockFile::setProcessPidAndState(unsigned int iPid,State iState){
	IAS_TRACER;
	StringStream ssProcessInfo;
	ssProcessInfo<<iPid;
	ssProcessInfo<<" "<<(int)iState;
	writeContent(ssProcessInfo.str());
}
/*************************************************************************/
void ProcessLockFile::getProcessPidAndState(unsigned int& iPid,State& iState){
	IAS_TRACER;

	iPid=0;
	iState=PS_ENDED;

	String strTmp;
	readContent(strTmp);
	StringStream ssTmp(strTmp);
	ssTmp>>iPid;
	int iTmp;
	ssTmp>>iTmp;
	iState=(State)iTmp;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"pid="<<iPid<<", state="<<(int)iState);
}
/*************************************************************************/
String ProcessLockFile::getFileName( const ::org::invenireaude::sm::cfg::Service* pService,
						             int iInstanceIdx){
	IAS_TRACER;

	StringStream ssFileName;
	ssFileName<<pService->getName();
	ssFileName<<"-"<<iInstanceIdx<<".lck";

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"File:"<<ssFileName.str());

	return ssFileName.str();
}
/*************************************************************************/
}
}
}
