/*
 * File: IAS-CommonLib/src/commonlib/sys/ipc/SharedMemory.cpp
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
#include "SharedMemory.h"

#include <commonlib/commonlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

namespace IAS {
namespace IPC {

/*************************************************************************/
SharedMemory::Descriptor::Descriptor(ResourceDescriptor::Mode iMode) throw() :
	ResourceDescriptor(iMode),iSize(0),pAddress(NULL) {
	IAS_TRACER;
}
/*************************************************************************/
void SharedMemory::Descriptor::setSize(int iSize) {
	IAS_TRACER;
	if(iSize < 0 )
		IAS_THROW(BadUsageException("setSize:iSize < 0"));
	this->iSize=iSize;
}
/*************************************************************************/
int SharedMemory::Descriptor::getSize() const {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Size: "<<iSize);
	return iSize;
}
/*************************************************************************/
void SharedMemory::Descriptor::setAddress(void*  pAddress) {
	IAS_TRACER;
	this->pAddress=pAddress;
}
/*************************************************************************/
void* SharedMemory::Descriptor::getAddress() const {
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Address: "<<pAddress);
	return pAddress;
}
/*************************************************************************/

/*************************************************************************/
SharedMemory::SharedMemory(const SharedMemory::Descriptor& aDescriptor) :
	aDescriptor(aDescriptor), iShmId(-1) {
	IAS_TRACER;
	init();
}
/*************************************************************************/
SharedMemory::~SharedMemory() throw () {
	IAS_TRACER;

	if(pAddress != NULL || pAddress != (void*) -1)
		shmdt(pAddress);

	if(aDescriptor.getDeleteOnCleanUp()){
		IAS_LOG(LogLevel::INSTANCE.isSystem(), "SharedMemory will be deleted: "<<iShmId);
		shmctl(iShmId, IPC_RMID, NULL);
	}
}
/*************************************************************************/
void SharedMemory::init() {
	IAS_TRACER;

	key_t key = aDescriptor.getKey();

	iSize = aDescriptor.getSize();
	iShmId = shmget(key, iSize, aDescriptor.getOpenFlags());

	if (iShmId == -1) {
		IAS_THROW(SystemException("SharedMemory::shmget",errno));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "SharedMemory of "<<iSize<<", iShmId="<<iShmId);

	pAddress = aDescriptor.getAddress();
	pAddress = shmat(iShmId,pAddress,0);
	if(pAddress == (void *) -1){
		IAS_THROW(SystemException("SharedMemory::shmat",errno));
	}

	refreshInfo();
}
/*************************************************************************/
void SharedMemory::refreshInfo(){
	IAS_TRACER;
	struct shmid_ds shmInfo;
	int iRes = shmctl(iShmId, IPC_STAT, &shmInfo);
	if(iRes == -1)
		IAS_THROW(SystemException("shmctl(..,IPC_RMID, ..)"));

	iSize = shmInfo.shm_segsz;

	IAS_LOG(LogLevel::INSTANCE.isSystem(), "SharedMemory updated size= "<<iSize<<", iShmId="<<iShmId);
}
/*************************************************************************/
int SharedMemory::getSize() const{
	IAS_TRACER;
	return iSize;
}
/*************************************************************************/
void* SharedMemory::getAddress() const{
	IAS_TRACER;
	return pAddress;
}
/*************************************************************************/
}
}
