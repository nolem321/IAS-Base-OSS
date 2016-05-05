/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/PersistentCacheStorage.h
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
#ifndef _IAS_QS_Workers_Proc_Cache_PersistentCacheStorage_H_
#define _IAS_QS_Workers_Proc_Cache_PersistentCacheStorage_H_

#include <commonlib/commonlib.h>
#include "WorkerCache.h"
#include <dm/datamodel.h>

#include <qs/workers/proc/prog/ProgramSet.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace Cache {

/*************************************************************************/
/** The PersistentCacheStorage class.
 *
 */
class PersistentCacheStorage : public WorkerCache::BucketStorage{
public:

	virtual ~PersistentCacheStorage() throw();

	virtual void createBucket(WorkerCache::Bucket* pBucket);

	virtual void fetchBucket(WorkerCache::Bucket* pBucket);
	virtual void fetchBucketItems(WorkerCache::Bucket* pBucket, size_t iSinceVersion = 0);
	virtual void updateBucket(WorkerCache::Bucket* pBucket);

	virtual void deleteBucket(WorkerCache::Bucket* pBucket);

	virtual void createOrUpdateBucketItem(WorkerCache::Bucket* pBucket,
			const WorkerCache::Bucket::ItemEntry* pValue);


protected:
	PersistentCacheStorage(const String& strPackage, class GlobalContext* pGlobalContext);

	String strPackage;

	IAS_DFT_FACTORY<Workers::Proc::Prog::ProgramSet>::PtrHolder ptrProgramSet;

	friend class Factory<PersistentCacheStorage>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Cache_PersistentCacheStorage_H_ */
