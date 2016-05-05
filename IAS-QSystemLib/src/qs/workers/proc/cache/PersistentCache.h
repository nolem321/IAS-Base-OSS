/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/PersistentCache.h
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
#ifndef _IAS_QS_Workers_Proc_Cache_PersistentCache_H_
#define _IAS_QS_Workers_Proc_Cache_PersistentCache_H_

#include <commonlib/commonlib.h>

#include "WorkerCache.h"

#include <org/invenireaude/qsystem/workers/cache/PersistentCache.h>
#include "PersistentCacheStorage.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;
namespace Cache {

class PersistentCacheStorage;

/*************************************************************************/
/** The PersistentCache class.
 *
 */
class PersistentCache : public WorkerCache {
public:

	virtual ~PersistentCache() throw();


protected:
	PersistentCache(const ::org::invenireaude::qsystem::workers::cache::PersistentCache* pPersistentCache,
					GlobalContext* pGlobalContext);

	IAS_DFT_FACTORY<PersistentCacheStorage>::PtrHolder ptrStorage;

	friend class Factory<PersistentCache>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Cache_PersistentCache_H_ */
