/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/PersistentCache.cpp
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
#include "PersistentCache.h"
#include <qs/log/LogLevel.h>


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Cache {

/*************************************************************************/
PersistentCache::PersistentCache(const ::org::invenireaude::qsystem::workers::cache::PersistentCache* pPersistentCache,
								 GlobalContext* pGlobalContext):
	ptrStorage(IAS_DFT_FACTORY<PersistentCacheStorage>::Create(pPersistentCache->getPackage(),pGlobalContext)){

	IAS_TRACER;

	if(pPersistentCache->isSetSize())
		setMaxSize(pPersistentCache->getSize());

	setStorage(ptrStorage);
}
/*************************************************************************/
PersistentCache::~PersistentCache() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
}
}
