/*
 * File: IAS-CommonLib/src/commonlib/caches/CacheBase.h
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

#ifndef IAS_CACHEBASE_H_
#define IAS_CACHEBASE_H_

#include "CacheInterface.h"
#include <map>
#include "../memory.h"

/*
 *
 */
namespace IAS {
namespace Cache {


/*************************************************************************/
/** The base of cache template classes.
 *
 */

template<class TR, class TK>
/** The class. */
 class CacheBase: public CacheInterface<TR,TK> {

public:

	enum EntryStates{
		ES_NONE        = 0,
		ES_IN_PROGRESS = 1,
		ES_READY       = 2
	};

	class CacheEntry{
	public:

		CacheEntry():iHits(0),iState(ES_NONE){}
		virtual ~CacheEntry(){};

		void setResource(TR* pResource){
			ptrResource=pResource;
			iState=ES_READY;
		}

		TR* getResource(){

		   if(iState == ES_READY)
			   return ptrResource.getPointer();
		   else{
			   IAS_THROW(IAS::InternalException("iState != ES_READY"));
		   }
		}

		void setInProgress(){
			iState=ES_IN_PROGRESS;
		}

		bool  isReady(){
			return iState == ES_READY;
		}

	protected:

		typename ::IAS::MemoryManagerFactory< TR >::PtrHolder ptrResource;
		int iHits;
		EntryStates iState;
	};


	class CacheStats{
	public:
		virtual ~CacheStats(){};
		CacheStats():iHits(0),iMisses(0){};
		void registerHit(){ iHits++;};
		void registerMiss(){ iMisses++;};

	protected:

		int iHits;
		int iMisses;

		friend class ::IAS::Factory<CacheStats>;
	};


};

}
}

#endif /* SIMPLECACHE_H_ */
