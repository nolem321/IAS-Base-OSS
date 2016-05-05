/*
 * File: IAS-CommonLib/src/commonlib/sys/fs/FileLock.cpp
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
#include "FileLock.h"

#include <commonlib/commonlib.h>

#include <unistd.h>
#include <fcntl.h>

namespace IAS {
namespace SYS {
namespace FS {

/*************************************************************************/
FileLock::FileAutoClose::FileAutoClose(int iFD):iFD(iFD){};
/*************************************************************************/
FileLock::FileAutoClose::~FileAutoClose(){
	if(iFD >= 0)
		close(iFD);
}
/*************************************************************************/
FileLock::FileLock(const String& strFileName):fileHolder(-1),strFileName(strFileName){
	IAS_TRACER;

	this->strFileName=strFileName;

	fileHolder.iFD = open(strFileName.c_str(), O_RDWR | O_CREAT , 0664);

	if(fileHolder.iFD < 0)
		IAS_THROW(SystemException(strFileName+" : (FileLock::init): ",errno));

}
/*************************************************************************/
FileLock::~FileLock() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void FileLock::lock(){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
		IAS_THROW(InternalException(strFileName+" :FileLock::lock"));

	struct flock fl;

	fl.l_type   = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;
	fl.l_len    = 0;
	fl.l_pid    = getpid();

	int iRes = fcntl(fileHolder.iFD, F_SETLKW, &fl);
	if(iRes < -1)
		IAS_THROW(SystemException(strFileName+" : lock :",errno));
}
/*************************************************************************/
bool FileLock::lockNoWait(){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
		IAS_THROW(InternalException(strFileName+" :FileLock::lock"));

	struct flock fl;

	fl.l_type   = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;
	fl.l_len    = 0;
	fl.l_pid    = getpid();

	return fcntl(fileHolder.iFD, F_SETLK, &fl) == 0;
}
/*************************************************************************/
void FileLock::unlock(){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
		IAS_THROW(InternalException("FileLock::unlock"));

	struct flock fl;

	fl.l_type   = F_UNLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;
	fl.l_len    = 0;
	fl.l_pid    = getpid();

	int iRes = fcntl(fileHolder.iFD, F_SETLK, &fl);

	if(iRes < -1)
		IAS_THROW(SystemException(strFileName+" : unlock : ",errno));
}
/*************************************************************************/
bool FileLock::isLocked(){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
		IAS_THROW(InternalException("FileLock::unlock"));

	struct flock fl;

	fl.l_type   = F_WRLCK;
	fl.l_whence = SEEK_SET;
	fl.l_start  = 0;
	fl.l_len    = 0;
	fl.l_pid    = getpid();

	fcntl(fileHolder.iFD, F_GETLK, &fl);

	return fl.l_type != F_UNLCK;
}
/*************************************************************************/
void FileLock::writeContent(const String& strContent){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
			IAS_THROW(InternalException("FileLock::writeContent"));

	lseek(fileHolder.iFD,SEEK_SET,0);
	ftruncate(fileHolder.iFD,0);
	int iLen = strContent.length();
	int iRes = write(fileHolder.iFD,strContent.c_str(),iLen);

	if(iRes != iLen)
		IAS_THROW(SystemException(strFileName+" : FileLock::writeContent : ",errno));
}
/*************************************************************************/
void FileLock::readContent(String& strContent){
	IAS_TRACER;

	if(fileHolder.iFD < 0)
			IAS_THROW(InternalException("FileLock::readContent"));

	lseek(fileHolder.iFD,SEEK_SET,0);

	char sBuf[4096];

	lseek(fileHolder.iFD,SEEK_SET,0);

	int iLen = read(fileHolder.iFD,sBuf,4096);

	if(iLen < 0)
		IAS_THROW(SystemException(strFileName+" : FileLock::readContent: ",errno));

	strContent.assign(sBuf,iLen);
}
/*************************************************************************/
}
}
}
