/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/CacheStore.cpp
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
#include "CacheStore.h"
#include <qs/log/LogLevel.h>

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Cache {

/*************************************************************************/
CacheStore::CacheStore(){
	IAS_TRACER;
}
/*************************************************************************/
CacheStore::~CacheStore() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CacheStore::addCache(const String& strName, WorkerCache* pWorkerCache){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmCaches.count(strName) > 0)
		IAS_THROW(AlreadyExists(String("cache: ")+strName));

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strName);

	hmCaches[strName]=pWorkerCache;
}
/*************************************************************************/
WorkerCache* CacheStore::lookup(const String& strName){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	if(hmCaches.count(strName) == 0)
		IAS_THROW(ItemNotFoundException(String("cache: ")+strName));

	return hmCaches.at(strName);

}
/*************************************************************************/

}
}
}
}
}
