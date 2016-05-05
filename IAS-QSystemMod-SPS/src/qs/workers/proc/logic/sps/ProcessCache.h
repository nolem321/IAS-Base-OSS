/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/ProcessCache.h
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
#ifndef _IAS_QS_Workers_Proc_Logic_SPS_ProcessCache_H_
#define _IAS_QS_Workers_Proc_Logic_SPS_ProcessCache_H_

#include <commonlib/commonlib.h>

#include "ProcessCacheEntry.h"
#include "ProcessDataStore.h"
#include "CacheBase.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
/** The ProcessCache class.
 *
 */
class ProcessCache :
		protected CacheBase,
		public InstanceFeature<ProcessCache>{
public:
	virtual ~ProcessCache() throw();

	ProcessCacheEntryPtr createEntry(const String& strProcessName);
	ProcessCacheEntryPtr getEntry(const String& strKey);

	void synchronize(ProcessCacheEntry* pProcessCacheEntry);

	void returnToCache(ProcessCacheEntryPtr& ptrProcessCacheEntry);

	typedef std::list<ProcessCacheEntryPtr> EntriesList;

	void getEntriesToSchedule(EntriesList& lstEntries, int iMaxEntries = 10);
	void getEntriesToClean(EntriesList& lstEntries, int iMaxEntries = 10);

	static void CreateInstanceSafely();

protected:

	ProcessCache();

	IAS_DFT_FACTORY<ProcessDataStore>::PtrHolder ptrDataStore;

	Mutex 				                      mutex;

	String strKeyPrefix;
	long   iCounter;

	friend class Factory<ProcessCache>;

};

/*************************************************************************/
}
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Logic_SPS_ProcessCache_H_ */
