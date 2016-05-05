/*
 * File: IAS-CommonLib/src/commonlib/sys/fs/DirectoryReader.cpp
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
#include "DirectoryReader.h"

#include <commonlib/commonlib.h>

#include <sys/types.h>
#include <dirent.h>
#include <algorithm>

#include <sys/stat.h>
#include <unistd.h>

namespace IAS {
namespace SYS {
namespace FS {
/*************************************************************************/
DirectoryReader::DirectoryReader(const String& strDir):strDir(strDir){
	IAS_TRACER;
}
/*************************************************************************/
DirectoryReader::~DirectoryReader() throw(){
	IAS_TRACER;
}
/*************************************************************************/
const DirectoryReader::EntriesList& DirectoryReader::getEntries() const{
	IAS_TRACER;
	return lstEntries;
}
/*************************************************************************/
#ifdef __linux
static inline DirectoryReader::FileType _convertedTypes(unsigned char c) {

	switch (c) {
	case DT_BLK:
		return DirectoryReader::FT_BLOCKDEV;
	case DT_CHR:
		return DirectoryReader::FT_CHARDEV;
	case DT_DIR:
		return DirectoryReader::FT_DIR;
	case DT_FIFO:
		return DirectoryReader::FT_PIPE;
	case DT_LNK:
		return DirectoryReader::FT_LINK;
	case DT_REG:
		return DirectoryReader::FT_FILE;
	case DT_SOCK:
		return DirectoryReader::FT_SOCKET;
	case DT_UNKNOWN:
		return DirectoryReader::FT_UNKNOWN;
	}

	IAS_THROW(InternalException("Unkown file type in _convertedTypes."));
}
#endif
/*************************************************************************/
static inline DirectoryReader::FileType _convertedTypesForFile(const String& strBase, const char* sName) {

	String strFullName(strBase);
	strFullName+="/";
	strFullName+=sName;

	struct stat theInfo;

	if(lstat(strFullName.c_str(),&theInfo) != 0)
		IAS_THROW(SystemException(sName));

	if(S_ISREG(theInfo.st_mode))
		return DirectoryReader::FT_FILE;

	if(S_ISDIR(theInfo.st_mode))
		return DirectoryReader::FT_DIR;

	if(S_ISCHR(theInfo.st_mode))
		return DirectoryReader::FT_CHARDEV;

	if(S_ISBLK(theInfo.st_mode))
		return DirectoryReader::FT_BLOCKDEV;

	if(S_ISFIFO(theInfo.st_mode))
		return DirectoryReader::FT_PIPE;

	if(S_ISLNK(theInfo.st_mode))
		return DirectoryReader::FT_LINK;

	if(S_ISSOCK(theInfo.st_mode))
		return DirectoryReader::FT_SOCKET;

	return DirectoryReader::FT_UNKNOWN;
}
/*************************************************************************/
DirectoryReader::Entry::Entry(FileType iType, String   strFile){
	this->iType=iType;
	this->strFile=strFile;
}
/*************************************************************************/
bool compare(const DirectoryReader::Entry* first, const DirectoryReader::Entry* second){
	return first->strFile.compare(second->strFile) < 0;
}
/*************************************************************************/
void DirectoryReader::read(){
	IAS_TRACER;

	lstEntries.clear();

   DIR* pDir;

   struct dirent  aDirent;
   struct dirent* pDirent;

   if( (pDir=opendir(strDir.c_str())) == NULL)
		   IAS_THROW(SystemException(strDir+="opendir"));

   pDirent=&aDirent;

   while( readdir_r(pDir,&aDirent,&pDirent) == 0 && pDirent != NULL) {

	   IAS_DFT_FACTORY<Entry>::PtrHolder ptrEntry;

#ifdef __linux
	   ptrEntry = IAS_DFT_FACTORY<Entry>::Create(_convertedTypes(pDirent->d_type),pDirent->d_name);
#else
	   ptrEntry = IAS_DFT_FACTORY<Entry>::Create(_convertedTypesForFile(strDir,pDirent->d_name),pDirent->d_name);
#endif


	   lstEntries.push_back(ptrEntry.pass());
   }

   std::sort(lstEntries.begin(),lstEntries.end(),compare);
}
/*************************************************************************/
}
}
}
