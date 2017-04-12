/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/shared/System.cpp
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
#include "System.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>
#include <string.h>

namespace IAS {
namespace QS {
namespace SHM {
namespace Shared {
/*************************************************************************/
const System::Version System::CSoftwareVersion(0,1,1);
/*************************************************************************/
System::Version::Version(Number iMajor, Number iMinor, Number iRelease):
		iMajor(iMajor),iMinor(iMinor),iRelease(iRelease){}
/*************************************************************************/
System::Version::Version(const Version& other):
		iMajor(other.iMajor),iMinor(other.iMinor),iRelease(other.iRelease){}
/*************************************************************************/
bool System::Version::isCompatible(const Version& other)const{

	return iMajor == other.iMajor &&
		   iMinor == other.iMinor &&
		   iRelease <= other.iRelease;

}/*************************************************************************/
String System::Version::toString()const{
	StringStream ssTmp;
	ssTmp<<"Ver. "<<(int)iMajor<<"."<<(int)iMinor<<"."<<(int)iRelease;
	return ssTmp.str();
}
/*************************************************************************/
System::System(const String& strName):
	systemVersion(CSoftwareVersion),
	mutexSystem(true,true),
	pContentStorage(NULL),
	pSessionTable(NULL),
	pQueueTable(NULL){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),strName<<" created at: "<<((void*)this));

	::strncpy(sName,strName.c_str(),C_MaxSysNameLength);
}
/*************************************************************************/
SharedMemorySegment::SharedMemorySegment():
	pAddress(NULL),
	iSize(0){};
/*************************************************************************/
System::~System(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isError(),"Internal Error : System destroyed.");

}
/*************************************************************************/
}
}
}
}
