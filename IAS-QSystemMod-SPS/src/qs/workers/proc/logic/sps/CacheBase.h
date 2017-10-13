/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/CacheBase.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_CacheBase_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_CacheBase_H_

#include <commonlib/commonlib.h>


#include "ProcessCacheEntry.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {


/*************************************************************************/
/** The Cache class.
 *
 */
class CacheBase{

public:
	virtual ~CacheBase() throw();


protected:
	CacheBase(int iMaxEntries = CMaxEntries)throw();
	Mutex 				                      mutex;

	void insert(ProcessCacheEntryPtr ptrCacheEntry);
	bool lookup(const String& strKey, ProcessCacheEntryPtr &ptrEntry);

private:

	typedef HashMapWithStringKey<ProcessCacheEntryPtr> EntriesMap;

	EntriesMap hmEntriesOne;
	EntriesMap hmEntriesTwo;

	EntriesMap* pRecent;
	EntriesMap* pOld;

	void swapNoLock();

	static const int CMaxEntries = 10;

	int iMaxEntries;

	friend class Factory<CacheBase>;
};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_Cache_H_ */
