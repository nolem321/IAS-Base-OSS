/*
 * File: IAS-QSystemLib/src/qs/workers/proc/wcm/cache/Context.cpp
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
#include "Context.h"

#include <qs/log/LogLevel.h>

#include "../../GlobalContext.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace WCM {
namespace Cache {

/*************************************************************************/
Context::Context(GlobalContext *pGlobalContext)throw():
	pCacheStore(pGlobalContext->getCacheStore()){
	IAS_TRACER;
}

/*************************************************************************/
Context::~Context() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Context::Entry* Context::lookupAndCreateIfNeed(const String& strCacheName){
	IAS_TRACER;


	if(hmCaches.count(strCacheName) == 0){
		Entry *pEntry = IAS_DFT_FACTORY<Entry>::Create();
		pEntry->pCache = pCacheStore->lookup(strCacheName);
		hmCaches[strCacheName]=pEntry;
		return pEntry;
	}else{
		return hmCaches.at(strCacheName);
	}

}
/*************************************************************************/
Proc::Cache::WorkerCache::Bucket*  Context::createBucket(const String& strCache, const String& strKey){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strCache<<", k="<<strKey);

	Entry *pEntry=lookupAndCreateIfNeed(strCache);

	pEntry->ptrAutoReturn.set(pEntry->pCache->createBucket(strKey),pEntry->pCache);

	return pEntry->ptrAutoReturn;
}
/*************************************************************************/
Proc::Cache::WorkerCache::Bucket*  Context::fetchBucket(const String& strCache, const String& strKey){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strCache<<", k="<<strKey);

	Entry *pEntry=lookupAndCreateIfNeed(strCache);

	pEntry->ptrAutoReturn.set(pEntry->pCache->getBucket(strKey),pEntry->pCache);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Done for: "<<strCache<<", k="<<strKey);

	return pEntry->ptrAutoReturn.getPointer();
}
/*************************************************************************/
Proc::Cache::WorkerCache::Bucket*  Context::getBucket(const String& strCache){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strCache);

	Entry *pEntry=lookupAndCreateIfNeed(strCache);
	if(pEntry->ptrAutoReturn.isNull())
		IAS_THROW(BadUsageException(String("Bucket was not initialized for cache: ")+strCache));

	return pEntry->ptrAutoReturn;
}
/*************************************************************************/
void Context::deleteBucket(const String& strCache, const String& strKey){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strCache<<", k="<<strKey);

	Entry *pEntry=lookupAndCreateIfNeed(strCache);

	pEntry->pCache->deleteBucket(strKey);
	pEntry->ptrAutoReturn.forget();

}
/*************************************************************************/
void Context::releaseBucket(const String& strCache, const String& strKey){
	IAS_TRACER;
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Cache: "<<strCache<<", k="<<strKey);

	if(hmCaches.count(strCache) == 0)
		return;

	hmCaches[strCache]->ptrAutoReturn.returnNow();

}
/*************************************************************************/
void Context::commit(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Context Committing ... ");

	for(CachesMap::iterator it=hmCaches.begin();
			                it!=hmCaches.end();it++)
		it->second->ptrAutoReturn.returnNow();

}
/*************************************************************************/
void Context::rollback(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Context Rolling back ... ");


	for(CachesMap::iterator it=hmCaches.begin();
				            it!=hmCaches.end();it++)
		it->second->ptrAutoReturn.forget();

}
/*************************************************************************/
}
}
}
}
}
}
