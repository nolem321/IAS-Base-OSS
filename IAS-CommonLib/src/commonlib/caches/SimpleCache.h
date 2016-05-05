/*
 * File: IAS-CommonLib/src/commonlib/caches/SimpleCache.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef SIMPLECACHE_H_
#define SIMPLECACHE_H_

#include "../logger/logger.h"
#include "../memory/ma/PtrHolder.h"

#include <map>

#include "CacheBase.h"

/*************************************************************************/
/** The simple cache template.
 *
 */
namespace IAS {
namespace Cache {

template<class TR, class TK>
/** The class. */
 class SimpleCache : public CacheBase<TR,TK> {


	class SimpleCacheEntry : public CacheBase<TR,TK>::CacheEntry { friend class ::IAS::Factory<SimpleCacheEntry>;	};
	class SimpleCacheStats : public CacheBase<TR,TK>::CacheStats { friend class ::IAS::Factory<SimpleCacheStats>;};

	typedef std::map<TK, SimpleCacheEntry* > EntriesMap;



public:

	SimpleCache(){
		IAS_TRACER;
		createStats();
	};

	virtual void createStats(){
		IAS_TRACER;
		ptrCacheStats = IAS_DFT_FACTORY<SimpleCacheStats>::Create();
	}

	virtual ~SimpleCache(){
		IAS_TRACER;
		for(typename EntriesMap::iterator it= hmEntries.begin();
			it !=  hmEntries.end();
			it ++){
			IAS_DFT_FACTORY< SimpleCacheEntry >::Free(it->second);
		}

	};

	virtual TR* getResource(const TK& key){
		IAS_TRACER;

		TR* pResource =  NULL;

		if(hmEntries.count(key) > 0){
			IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(), "Cache entry found.");

			if(hmEntries[key]->isReady()){
				IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(), "Resource ready.");
				pResource = hmEntries[key]->getResource();
			}else{
				IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(), "Resource not ready.");
			}

		}else{


			try{

				hmEntries[key]=IAS_DFT_FACTORY<SimpleCacheEntry>::Create();
				pResource = retrieve(key);
				hmEntries[key]->setResource(pResource);

			}catch(IAS::Exception &e){
				//TODO (L) Do we have anything to say here ?
				throw e;
			}
		}

		return pResource;
	}

	void dumpEntries(std::ostream& os){

		for( typename EntriesMap::iterator it = hmEntries.begin();
			 it != hmEntries.end();
			 it++){
			SimpleCacheEntry *pEntry = it->second;
			os<<it->first<<":";
			if(pEntry->isReady())
				os<<(void*)(pEntry->getResource());
				else
				os<<"not ready";
			os<<"\n";
		}

	}

protected:

	EntriesMap hmEntries;
	virtual TR* retrieve(const TK& key) = 0;
	typename IAS_DFT_FACTORY<SimpleCacheStats>::PtrHolder ptrCacheStats;
};

}
}

#endif /* SIMPLECACHE_H_ */
