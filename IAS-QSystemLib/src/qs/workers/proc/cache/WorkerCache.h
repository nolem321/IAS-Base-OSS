/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/WorkerCache.h
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
#ifndef _IAS_QS_Workers_Proc_Cache_WorkerCache_H_
#define _IAS_QS_Workers_Proc_Cache_WorkerCache_H_

#include <commonlib/commonlib.h>
#include <commonlib/caches/BucketCache.h>
#include <dm/datamodel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Cache {

/*************************************************************************/

typedef ::IAS::Cache::StandardBucketCache< ::IAS::DM::DataObjectPtr > WorkerCache;

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Workers_Proc_Cache_WorkerCache_H_ */
