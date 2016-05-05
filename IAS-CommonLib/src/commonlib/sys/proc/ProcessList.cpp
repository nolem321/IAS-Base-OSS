/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/ProcessList.cpp
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
#include "ProcessList.h"

#include <commonlib/commonlib.h>
#include "commonlib/sys/fs/DirectoryReader.h"
#include "commonlib/streams/InputFile.h"

#include <stdlib.h>

namespace IAS {
namespace SYS {
using namespace FS;
namespace Proc {

/*************************************************************************/
ProcessList::ProcessList() {
	IAS_TRACER;
	ptrDirectoryReader = IAS_DFT_FACTORY<DirectoryReader>::Create("/proc");
}
/*************************************************************************/
ProcessList::~ProcessList() throw () {
	IAS_TRACER;
}
/*************************************************************************/
const ProcessList::EntriesList& ProcessList::getEntries() const {
	IAS_TRACER;
	return lstEntries;
}

/*************************************************************************/
ProcessList::Entry* ProcessList::createEntry(int iPid) const {
	IAS_TRACER;

	StringStream ssFileName;
	ssFileName << "/proc/" << iPid << "/stat";

	IAS_DFT_FACTORY<InputFile>::PtrHolder ptrStatFile;
	ptrStatFile=IAS_DFT_FACTORY<InputFile>::Create(ssFileName.str());
	ptrStatFile->open();
	if (!ptrStatFile->isOpenedAndGood())
		IAS_THROW(SystemException(ssFileName.str()+=":error when reading."));

	std::istream& is = ptrStatFile->getStreamRef();

	IAS_DFT_FACTORY<Entry>::PtrHolder ptrEntry;
	ptrEntry = IAS_DFT_FACTORY<Entry>::Create();

	char sLine[1024];

	sLine[0] = 0;
	is.getline(sLine, 1024);

	if (iPid != atoi(sLine))
		IAS_THROW(InternalException("iPid != atoi(buf)"));

	ptrEntry->iPid=iPid;

	char *sCursor = strchr(sLine, ' ');
	if (!sCursor)
		IAS_THROW(InternalException("/proc/*/stat:parse error (1)"));

	sCursor += 2;
	char *sTmp = strrchr(sCursor, ')');
	if (!sTmp)
		IAS_THROW(InternalException("/proc/*/stat:parse error (2)"));

	int iCmdLen = sTmp - sCursor;
	ptrEntry->strName.assign(sCursor, iCmdLen);

	sCursor = sTmp + 2;

	int iIdx = sscanf(sCursor, "%c %d %u %u %u "
		"%u %lu "
		"%*u %*u %*u %*u "
		"%lu %lu %ld %ld "
		"%ld %ld %ld "
		"%*d %*u %*u %*d %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u "
		"%d %d",
		&ptrEntry->cState, &ptrEntry->iParentPid, &ptrEntry->iPGrp, &ptrEntry->iSession, &ptrEntry->iTTY,
		&ptrEntry->iTGid, &ptrEntry->iFlags,
		&ptrEntry->utime, &ptrEntry->stime, &ptrEntry->cutime, &ptrEntry->cstime,
		&ptrEntry->iPriority, &ptrEntry->iNice, &ptrEntry->iNLWP,
		&ptrEntry->iExitSignal, &ptrEntry->iProcessor);

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"["<<iPid<<"]"<<ptrEntry->strName<<":"<<ptrEntry->cState<<":"<<ptrEntry->utime);

	return ptrEntry.pass();
}
/*************************************************************************/
void ProcessList::read() {
	IAS_TRACER;

	lstEntries.clear();
	hmEntriesByPid.clear();

	ptrDirectoryReader->read();

	const DirectoryReader::EntriesList& lstEntries = ptrDirectoryReader->getEntries();

	for (DirectoryReader::EntriesList::const_iterator it = lstEntries.begin(); it != lstEntries.end(); it++) {

		if ((*it)->iType != DirectoryReader::FT_DIR)
			continue;

		int iPid = atoi((*it)->strFile.c_str());
		if (iPid <= 0)
			continue;

		Entry* pEntry = createEntry(iPid);
		this->lstEntries.push_back(pEntry);
		hmEntriesByPid[iPid]=pEntry;
	}

}
/*************************************************************************/
const ProcessList::Entry* ProcessList::getEntryByPid(int iPid) const{
	IAS_TRACER;

	EntriesMap::const_iterator it=hmEntriesByPid.find(iPid);

	if(it == hmEntriesByPid.end()) {
		IAS_THROW(ItemNotFoundException("ProcessList::getEntryByPid"));
	}

	return it->second;

}
/*************************************************************************/
}
}
}
