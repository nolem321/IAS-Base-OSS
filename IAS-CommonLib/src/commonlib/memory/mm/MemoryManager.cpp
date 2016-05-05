/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/MemoryManager.cpp
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

#include "MemoryManager.h"
#include "commonlib/logger/logger.h"
#include "commonlib/logger/StackTrace.h"
#include "commonlib/logger/StackTraceContainer.h"
#include "commonlib/memory/memory.h"

#include <stdlib.h>

namespace IAS {

MemoryManager* MemoryManager::pInstance = NULL;
Allocator*     MemoryManager::pAllocator = NULL;

/*************************************************************************/
MemoryManager::MemoryManager():
	iNewEntries(0),
	pMemory(0),
	iFree(0),
	iTotalEntries(0),
	iCurEntries(0),
	iInstances(0){

	//iFree=10000000;
	//pMemory = new unsigned char[iFree];

//	this->bCheckPointersOnReturn=false;
}
/*************************************************************************/
MemoryManager::~MemoryManager() throw () {
}
/*************************************************************************/
void MemoryManager::clearNewFlag() {

	EntryMap::iterator iter;
	IAS_LOG(LogLevel::INSTANCE.isMemory(),"Clearing New Flag.");

	Mutex::Locker locker(theLock);

	for (iter = hmEntries.begin(); iter != hmEntries.end(); iter++) {
		Entry& entry = iter->second;
		entry.bNewFlag = false;
	}
	iNewEntries = 0;
}
/*************************************************************************/
void MemoryManager::addEntry(const char* sFile, const char* sFun, int iLine, unsigned long lPtr) {

	Entry entry;

	entry.sFile = sFile;
	entry.sFun = sFun;
	entry.iLine = iLine;
	entry.bNewFlag = true;
	entry.lPtr = lPtr;

	bool bCheck = false;
	{
		Mutex::Locker locker(theLock);
		if (!(bCheck = hmEntries.count(lPtr) > 0)) {
			hmEntries[lPtr] = entry;
			iTotalEntries++;
			iCurEntries++;
			iNewEntries++;
		}
	}

	if (bCheck) {
		IAS_LOG(LogLevel::INSTANCE.isError(),"Duplicated entry: "<<((void*)lPtr));
		IAS_LOG(LogLevel::INSTANCE.isStackTrace(),"Stack: ");
		if (LogLevel::INSTANCE.isStackTrace()) {
			IAS_MY_STACK().printStack(std::cerr);
		}
	}

	IAS_LOG(IAS::LogLevel::INSTANCE.isMemory(), "N["<<(void*)lPtr<<"]:"<<sFile<<","<<sFun<<"("<<iLine<<"),s="<<hmEntries.size()
			<<":"<<iCurEntries<<":"<<iTotalEntries);

}

/*************************************************************************/
bool MemoryManager::removeEntry(unsigned long lPtr) {

	IAS_LOG(IAS::LogLevel::INSTANCE.isMemory(), "R["<<(void*)lPtr<<"]");

	int iCount = 0;
	{
		Mutex::Locker locker(theLock);
		iCount = hmEntries.count(lPtr);
		if (iCount > 0) {
			if (hmEntries[lPtr].bNewFlag)
				iNewEntries--;
			hmEntries.erase(lPtr);
			iCurEntries--;
		}
	}

	if (iCount == 0) {
		IAS_LOG(LogLevel::INSTANCE.isError(),"Missing entry: "<<((void*)lPtr));
		IAS_LOG(LogLevel::INSTANCE.isStackTrace(),"Stack: ");
		if (LogLevel::INSTANCE.isStackTrace()) {
			IAS_MY_STACK().printStack(std::cerr);
		}

		if(getenv("IAS_MEM_DUMP_ON_MISSING_ENTRY") != NULL){
			std::cerr<<"core dump as requested "<<std::endl;
			abort();
		}
	}

	return iCount != 0;
}
/*************************************************************************/
long MemoryManager::getNumerOfNew() const {
	IAS_TRACER;
	return iNewEntries;
}
/*************************************************************************/
void MemoryManager::printToStream(std::ostream& os) {
	printToStream(os,false);
}
/*************************************************************************/
void MemoryManager::printToStream(std::ostream& os, bool bNewOnly) {

	Mutex::Locker locker(theLock);

	os << " >>>  MEMORY USAGE " << std::endl;
	os << " >>>  Total:     " << iTotalEntries << std::endl;
	os << " >>>  Current:   " << iCurEntries << "," << hmEntries.size() << std::endl;
	os << " >>>  New:       " << iNewEntries << std::endl;
	os << " >>>  Instances: " << iInstances << std::endl;
	EntryMap::iterator iter;

	for (iter = hmEntries.begin(); iter != hmEntries.end(); iter++) {

		Entry& entry = iter->second;

		if (!bNewOnly || entry.bNewFlag) {
			os << (entry.sFile) << ":" << (entry.sFun) << "(" << entry.iLine << "): ";
			os << "\t [" << ((void*) entry.lPtr) << "]";
			os << "(" << ((unsigned int) entry.iTID) << ")";
			if (entry.bNewFlag)
				os << " N";
			os << std::endl;
		}

	}/* for */

	os << std::endl;

	os<<"Waits:  "<<tsrMutexWaits<<std::endl;

}

/*************************************************************************/
void* MemoryManager::allocate(size_t iNumBytes) {

    void* p = operator new(iNumBytes);

	/*if(iFree < iNumBytes){
		std::cerr<<"OUT OF MEMORY!!!"<<std::endl;
		throw MemoryException(errno);
	}

	void *p=pMemory;
	iFree-=iNumBytes;
	pMemory+=iNumBytes;
    */
    if(p == NULL)
       throw MemoryException(errno);

	if (::IAS::LogLevel::INSTANCE.isMemoryTrace()) {

		const StackTrace& stack =
				IAS_MY_STACK();

		if (!stack.empty()) {
			const StackTrace::Entry& entry = stack.top();
			addEntry(entry.sFile, entry.sFun, entry.iLine, (unsigned long) p);
		} else {
			addEntry("noline", "nofun", 1, (unsigned long) p);
		}

	}

	return p;

}
/*************************************************************************/
bool MemoryManager::check(const void* p) {

	if (!::IAS::LogLevel::INSTANCE.isMemoryTrace()) {
		IAS_LOG(IAS::LogLevel::INSTANCE.isMemory(), "Check is not working in FAST_AND_FURIOUS mode["<<(void*)p<<"]");
		return true;
	}

	unsigned long lPtr=(unsigned long)p;

	IAS_LOG(IAS::LogLevel::INSTANCE.isMemory(), "C["<<(void*)lPtr<<"]");

	int iCount = 0;
	{
		Mutex::Locker locker(theLock,tsrMutexWaits);
		iCount = hmEntries.count(lPtr);
	}

	if (iCount == 0) {
		IAS_LOG(LogLevel::INSTANCE.isError(),"Missing entry: "<<((void*)lPtr));
		IAS_LOG(LogLevel::INSTANCE.isStackTrace(),"Stack: ");
		if (LogLevel::INSTANCE.isStackTrace()) {
			IAS_MY_STACK().printStack(std::cerr);
		}

		if(getenv("IAS_MEM_DUMP_ON_MISSING_ENTRY") != NULL){
			std::cerr<<"core dump as requested "<<std::endl;
			abort();
		}
	}

	return iCount != 0;
}
/*************************************************************************/
void MemoryManager::free(const void* p) {

	if (::IAS::LogLevel::INSTANCE.isMemoryTrace() && !removeEntry((unsigned long) p)){
		IAS_LOG(LogLevel::INSTANCE.isError(),"Missing entry: "<<((void*)p));
		IAS_MY_STACK().printStack(std::cerr);

		if(getenv("IAS_MEM_DUMP_ON_MISSING_ENTRY") != NULL){
			std::cerr<<"core dump as requested "<<std::endl;
			abort();
		}

	}else{
		::free( const_cast<void*>(p));
	}
}
/*************************************************************************/
}/* namespace IAS */
