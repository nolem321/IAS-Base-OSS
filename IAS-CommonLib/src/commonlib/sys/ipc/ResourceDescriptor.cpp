/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/ResourceDescriptor.cpp
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

#include "ResourceDescriptor.h"


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

namespace IAS {
namespace IPC {
/*************************************************************************/
ResourceDescriptor::ResourceDescriptor(ResourceDescriptor::Mode iMode) throw () :
	iMode(iMode), aKey(ResourceDescriptor::C_PRIVATE) {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "iMode="<<iMode);
}
/*************************************************************************/
ResourceDescriptor::~ResourceDescriptor(){
	IAS_TRACER;
}
/*************************************************************************/
int ResourceDescriptor::getOpenFlags() const {
	IAS_TRACER;

	int iFlags = 0664;

	switch (iMode) {
	case M_OWNER:
		return iFlags | IPC_CREAT | IPC_EXCL;
		break;
	case M_USER:
		return iFlags | IPC_CREAT;
		break;
	case M_CLEANER:
		return iFlags;
		break;
	default:
		IAS_THROW(BadUsageException("getOpenFlags:iMode"))
		;
	}
}
/*************************************************************************/
bool ResourceDescriptor::getDeleteOnCleanUp() const {
	IAS_TRACER;
	return iMode == M_CLEANER || iMode == M_OWNER;
}
/*************************************************************************/
void ResourceDescriptor::setKey(ResourceDescriptor::Key aKey) {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Key: "<<aKey);
	this->aKey = aKey;
}
/*************************************************************************/
void ResourceDescriptor::setKeyByToken(const String& strPath, int id){
	IAS_TRACER;

	if(id <= 0 || id > 255){
		IAS_THROW(BadUsageException("setKeyByToken:(id <= 0 || id > 255)"));
	}

	int aKey = ftok(strPath.c_str(),id);

	if(aKey == -1)
		IAS_THROW(SystemException("ftok"));

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Key: "<<aKey);
	this->aKey=aKey;
}
/*************************************************************************/
ResourceDescriptor::Key ResourceDescriptor::getKey() const {
	IAS_TRACER;
	return aKey == C_PRIVATE ? IPC_PRIVATE : aKey;
}
/*************************************************************************/

}
}
