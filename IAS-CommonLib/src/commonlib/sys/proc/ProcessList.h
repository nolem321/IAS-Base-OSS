/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/ProcessList.h
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
#ifndef _IAS_SYS_Proc_ProcessList_H_
#define _IAS_SYS_Proc_ProcessList_H_

#include "commonlib/types.h"
#include "commonlib/containers/PtrVector.h"

#include <map>

namespace IAS {
namespace SYS {
namespace FS {
class DirectoryReader;
}
namespace Proc {

/*************************************************************************/
/** The ProcessList class.
 *
 */
class ProcessList {
public:

	struct Entry {
		virtual ~Entry(){};

		int iPid;
		int iParentPid;

		char     cState;

		unsigned int iPGrp;
		unsigned int iSession;
		unsigned int iTTY;

		unsigned int iTGid;
		unsigned int tPgid;
		unsigned long int iFlags;

		unsigned long int utime;
		unsigned long int stime;
		long int cutime;
		long int cstime;
		long int iPriority;
		long int iNice;
		long int iNLWP;

		int iExitSignal;
		int iProcessor;

		long iStartTime;

		String strName;

		void init(){};
	};

	ProcessList();
	virtual ~ProcessList() throw();

	void read();

	typedef PtrVector<Entry> EntriesList;
	const EntriesList& getEntries() const;
	const Entry* getEntryByPid(int iPid) const;



protected:

	IAS_DFT_FACTORY< ::IAS::SYS::FS::DirectoryReader >::PtrHolder ptrDirectoryReader;

	EntriesList lstEntries;

	Entry* createEntry(int iPid)const;

	typedef std::map<int,Entry*> EntriesMap;
	EntriesMap                   hmEntriesByPid;

};

/*************************************************************************/
}
}
}

#endif /* _IAS_SYS_Proc_ProcessList_H_ */
