/*
 * File: IAS-CommonLib/src/commonlib/memory/sharable/SharedMemoryFile.cpp
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
/* ChangeLog:
 * 
 */

#include "SharedMemoryFile.h"
#include "commonlib/logger/logger.h"
#include "commonlib/exception/InternalException.h"
#include "commonlib/exception/SystemException.h"
#include "commonlib/tools/TypeTools.h"

#include <sys/mman.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <stdlib.h>

namespace IAS {

/*************************************************************************/
SharedMemoryFile::Descriptor::Descriptor():
	iDomain(DM_SHARED_MEMORY),
	iOpenMode(OM_CREATE_IF_NEEDED),
	iCloseMode(CM_DEATTACH),
	pAddress(0),
	iSize(0){
	IAS_TRACER;
}
/*************************************************************************/
SharedMemoryFile::Descriptor::Descriptor(const Descriptor& other):
	iDomain(other.iDomain),
	iOpenMode(other.iOpenMode),
	iCloseMode(other.iCloseMode),
	strName(other.strName),
	pAddress(other.pAddress),
	iSize(other.iSize){
	IAS_TRACER;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setDomain(Domain iDomain){
	IAS_TRACER;
	this->iDomain=iDomain;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setOpenMode(OpenMode iOpenMode){
	IAS_TRACER;
	this->iOpenMode=iOpenMode;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setCloseMode(CloseMode iCloseMode){
	IAS_TRACER;
	this->iCloseMode=iCloseMode;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setName(const String& strName){
	IAS_TRACER;
	this->strName=strName;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setAddress(void *pAddress){
	IAS_TRACER;
	this->pAddress=pAddress;
}
/*************************************************************************/
void SharedMemoryFile::Descriptor::setSize(size_t iSize){
	IAS_TRACER;
	this->iSize=iSize;
}
/*************************************************************************/
SharedMemoryFile::Descriptor::Domain SharedMemoryFile::Descriptor::getDomain() const{
	IAS_TRACER;
	return iDomain;
}
/*************************************************************************/
SharedMemoryFile::Descriptor::OpenMode SharedMemoryFile::Descriptor::getOpenMode() const {
	IAS_TRACER;
	return iOpenMode;
}
/*************************************************************************/
SharedMemoryFile::Descriptor::CloseMode SharedMemoryFile::Descriptor::getCloseMode() const {
	IAS_TRACER;
	return iCloseMode;
}
/*************************************************************************/
const String& SharedMemoryFile::Descriptor::getName() const {
	IAS_TRACER;
	return strName;
}
/*************************************************************************/
void* SharedMemoryFile::Descriptor::getAddress() const {
	IAS_TRACER;
	return pAddress;
}
/*************************************************************************/
size_t SharedMemoryFile::Descriptor::getSize() const {
	IAS_TRACER;
	return iSize;
}
/*************************************************************************/
/*************************************************************************/
SharedMemoryFile::SharedMemoryFile(const Descriptor& aDescriptor):
	aDescriptor(aDescriptor),
	bAlreadyExisted(false),
	pAddress(0),
	fd(-1){
	IAS_TRACER;

	accessFile();
	mapFile();

}
/*************************************************************************/
void SharedMemoryFile::accessFile() {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening memory: ["<<aDescriptor.strName<<"]:"
			<<aDescriptor.iOpenMode);

	if(aDescriptor.iDomain == Descriptor::DM_SHARED_MEMORY){

		int iOpenOptions = 0;

		switch(aDescriptor.iOpenMode){

		case Descriptor::OM_ATTACH           : iOpenOptions = 0; break;

		case Descriptor::OM_CREATE_ALWAYS :
			shm_unlink(aDescriptor.strName.c_str());

		case Descriptor::OM_CREATE_IF_NEEDED    : iOpenOptions = O_CREAT /*| O_EXCL*/ ; break;

		default:
			IAS_THROW(InternalException("Unknown mode."));
		}

		if ((fd=shm_open(aDescriptor.strName.c_str(),
					iOpenOptions |  O_RDWR,
					S_IRUSR | S_IWUSR)) == -1)
			IAS_THROW(SystemException(aDescriptor.strName+" -> shm_open"));
	}

	struct stat info;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Opening memory: "<<aDescriptor.strName<<",fd = "<<fd);


	if(fstat(fd, &info) < 0)
		IAS_THROW(SystemException(aDescriptor.strName+" -> fstat" +TypeTools::IntToString(fd)));

	bAlreadyExisted = info.st_size > 0;

	if(bAlreadyExisted && aDescriptor.getSize() == 0)
		aDescriptor.setSize(info.st_size);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Attached: "<<info.st_size<<" bytes.");

}
/*************************************************************************/
void SharedMemoryFile::mapFile() {
	IAS_TRACER;

	if(!bAlreadyExisted){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Truncate to: "<<aDescriptor.iSize<<" bytes.");
		if(ftruncate(fd,aDescriptor.iSize)< 0)
			IAS_THROW(SystemException(aDescriptor.strName+" -> ftruncate"));
	}

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Attaching at: "<<(void*)aDescriptor.pAddress<<", "<<
			aDescriptor.iSize<<" bytes.");

	pAddress = mmap(aDescriptor.pAddress,
				    aDescriptor.iSize,
					PROT_READ | PROT_WRITE,
					(aDescriptor.pAddress==0) ? MAP_SHARED : MAP_FIXED | MAP_SHARED,
					fd,
					0);

	if(pAddress == NULL || pAddress == MAP_FAILED){
		IAS_THROW(SystemException(aDescriptor.strName+" -> mmap "));
	}

	IAS_LOG(LogLevel::INSTANCE.isSystem(),aDescriptor.strName<<" attached at: "<<pAddress);

}
/*************************************************************************/
SharedMemoryFile::~SharedMemoryFile() throw () {
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Cleanup of SharedMemoryFile: ["<<aDescriptor.strName<<"]");

	if(pAddress)
		munmap(pAddress,aDescriptor.iSize);

	if(fd >= 0)
		close(fd);

	if(aDescriptor.iDomain == Descriptor::DM_SHARED_MEMORY &&
		aDescriptor.iCloseMode == Descriptor::CM_DESTROY){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"Remove object: ["<<aDescriptor.strName<<"]");
		shm_unlink(aDescriptor.strName.c_str());
	}
}
/*************************************************************************/
size_t SharedMemoryFile::getSize() const{
	IAS_TRACER;
	return aDescriptor.iSize;
}
/*************************************************************************/
bool SharedMemoryFile::alreadyExisted() const{
	IAS_TRACER;
	return bAlreadyExisted;
}
/*************************************************************************/
void* SharedMemoryFile::getAddress() const{
	IAS_TRACER;
	if(!pAddress)
		IAS_THROW(InternalException("Null address in SharedMemoryFile::getAddress()."));
	return pAddress;
}
/*************************************************************************/
const SharedMemoryFile::Descriptor& SharedMemoryFile::getDescriptor() const{
	IAS_TRACER;
	return aDescriptor;
}
/*************************************************************************/
}/* namespace IAS */
