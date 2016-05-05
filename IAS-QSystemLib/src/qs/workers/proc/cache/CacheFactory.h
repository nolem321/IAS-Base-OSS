/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/CacheFactory.h
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
#ifndef _IAS_QS_Workers_Proc_Cache_CacheFactory_H_
#define _IAS_QS_Workers_Proc_Cache_CacheFactory_H_

#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/cache/Specification.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
class GlobalContext;

namespace Cache {

class CacheStore;

/*************************************************************************/
/** The CacheFactory class.
 *
 */
class CacheFactory {
public:

	static void CreateCaches(const ::org::invenireaude::qsystem::workers::cache::Specification* dmSpecification,
						   	 CacheStore *pCacheStore,
							 GlobalContext *pGlobalContext);

	static ::org::invenireaude::qsystem::workers::cache::Ext::SpecificationPtr
			CacheSpecsToDM(const String& strSpecs);

};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Cache_CacheFactory_H_ */
