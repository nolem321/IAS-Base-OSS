/*
 * File: IAS-CommonLib/src/commonlib/net/FileHandle.cpp
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
#include "FileHandle.h"

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>

#include <commonlib/tools/MiscTools.h>
#include <commonlib/logger/logger.h>

#include <commonlib/exception/BadUsageException.h>
#include <commonlib/exception/EndOfDataException.h>
#include <commonlib/threads/Thread.h>
namespace IAS {
namespace Net {

//TODO (M) MSG_NOSIGNAL - use and if not defined #warning

/*************************************************************************/
FileHandle::FileHandle(int iFileDescriptor):
	iFileDescriptor(iFileDescriptor),
	iTimeout(C_UnLimited),
	peer(peer){
	IAS_TRACER;
}
/*************************************************************************/
FileHandle::~FileHandle()throw(){
	IAS_TRACER;
	close();
}
/*************************************************************************/
void FileHandle::setNonBlocking(){

	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isInfo(), "Non blocking mode for fd="<<iFileDescriptor);

	int iFlags;

	if((iFlags=fcntl(iFileDescriptor, F_GETFL, 0)) == -1)
		IAS_THROW(SystemException("fcntl in SetNonBlocking mode:"))

	iFlags |= O_NONBLOCK;

	if(fcntl(iFileDescriptor, F_SETFL, iFlags) == -1)
			IAS_THROW(SystemException("fcntl in SetNonBlocking mode:"))

	this->iTimeout=C_NonBlock;
}
/*************************************************************************/
IBlockIO::Result  FileHandle::write(const void *pData, size_t iDataSize, size_t& iWritten){
	IAS_TRACER;

	//usleep(10000);
	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iDataSize;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"WRITE:"<<iDataSize<<" ["<<strData<<"]");
	}

	if(iTimeout > 0)
		if(!waitForData(WM_Write)){
			iWritten=0;
			return RC_OK;
		}

	ssize_t iResult = ::write(iFileDescriptor,pData,iDataSize);

	if(iResult < 0){
		if(errno == EAGAIN || errno == EWOULDBLOCK)
			return RC_WantWrite;

		if(errno == EPIPE)
			IAS_THROW(EndOfDataException("write - broken pipe"));

		IAS_THROW(SystemException("write",errno));
	}

	iWritten = iResult;
	return RC_OK;
}
/*************************************************************************/
IBlockIO::Result FileHandle::read(void *pData, size_t iBufferLen, size_t& iDataSize){
	IAS_TRACER;

	if(readUndone(pData,iBufferLen,iDataSize))
		return RC_OK;


	if(iTimeout >= 0)
	if(!waitForData(WM_Read)){
		iDataSize=0;
		return RC_OK;
	}

	ssize_t iResult = 0;

	{
		Thread::Cancellation ca(true);
		iResult = ::read(iFileDescriptor,pData,iBufferLen);
	}

	if(iResult < 0){

		IAS_LOG(LogLevel::INSTANCE.isError(),"READ:"<<(void*)pData<<"len="<<iBufferLen);

		if(errno == EAGAIN || errno == EWOULDBLOCK)
			return RC_WantRead;

		if(errno == EPIPE)
				IAS_THROW(EndOfDataException("read - broken pipe"));

		if(errno == 104)
					IAS_THROW(EndOfDataException("read - connection reset by peer"));


		IAS_THROW(SystemException("read",errno));
	}

	if(LogLevel::INSTANCE.isData()){
		String strData;
		for(int i=0;i<iResult;i++)
			strData += String("") + (*(((char*)pData)+i) >= ' ' ? *(((char*)pData)+i) : '.');
		IAS_LOG(LogLevel::INSTANCE.isData(),"READ:"<<iResult<<" ["<<strData<<"]");
	}

	iDataSize=iResult;

	return RC_OK;
}
/*************************************************************************/
void FileHandle::close(){
	IAS_TRACER;

	IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(), "close("<<iFileDescriptor<<")");

	int iResult;

	if(iFileDescriptor > 0){

		shutdown(iFileDescriptor, SHUT_RDWR);

		if(::close(iFileDescriptor) != 0)
			IAS_LOG(LogLevel::INSTANCE.isError(),"close("<<iFileDescriptor<<")="<<errno<<":"<<strerror(errno));
	}

}
/*************************************************************************/
void FileHandle::setTimeout(int iTimeout){
	IAS_TRACER;

	if(iTimeout != C_UnLimited && iTimeout < 0)
		IAS_THROW(BadUsageException("timeout: ")<<iTimeout);

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"fd("<<iFileDescriptor<<"), timeout: "<<iTimeout<<(this->iTimeout != C_NonBlock ? "ignored" : ""));

	if(this->iTimeout != C_NonBlock)
		this->iTimeout=iTimeout;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"fd("<<iFileDescriptor<<"), timeout: "<<this->iTimeout);
}
/*************************************************************************/
bool FileHandle::waitForData(WaitMode iMode){
	IAS_TRACER;

	 fd_set set;
	 struct timeval timeout;

	 FD_ZERO(&set);
	 FD_SET(iFileDescriptor, &set);

	 timeout.tv_sec = 0;
	 timeout.tv_usec = 1000*iTimeout;

	 IAS_LOG(LogLevel::INSTANCE.isInfo(),"fd("<<iFileDescriptor<<"), timeout: "<<iTimeout<<(this->iTimeout == C_NonBlock ? "ignored" : ""));

	 int iRC = ::select(iFileDescriptor + 1,
			 	 (iMode == WM_Read  ? &set : NULL),
				 (iMode == WM_Write ? &set : NULL),
				 &set,
				 &timeout);

	 IAS_LOG(LogLevel::INSTANCE.isInfo(),"rc="<<iRC);

	 switch(iRC){
	 	 case -1:
	 		 IAS_THROW(SystemException("select: ")<<iFileDescriptor)
			 break;
	 	 case 0:
	 		 return false;
	 		 break;
	 }

	 return true;
}
/*************************************************************************/
void FileHandle::setPeer(const Peer& peer){
	IAS_TRACER;
	this->peer=peer;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"FileHandle for: "<<peer);
}
/*************************************************************************/
const Peer& FileHandle::getPeer()const{
	return peer;
}
/*************************************************************************/
}
}
