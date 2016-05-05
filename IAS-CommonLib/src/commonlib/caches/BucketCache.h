/*
 * File: IAS-CommonLib/src/commonlib/caches/BucketCache.h
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
#ifndef _IAS_Cache_BucketCache_H_
#define _IAS_Cache_BucketCache_H_


#include <commonlib/memory/memory.h>
#include <commonlib/types.h>
#include <commonlib/logger/logger.h>

namespace IAS {
namespace Cache {


/*************************************************************************/
/** The BucketCache class.
 *  TODO (L) We can use pointers as hashmap keys but is it really significantly faster ?
 */



template<class K, class T,
	   class H = _Hash<K>,
	   class P = _EqualsTo<K>,
	   class A = IAS_DFT_FACTORY<std::pair<const K, T> > >
   class _BucketMap : public ias_std_unordered_map<K,T,H,P,A> {};



template<class BKT, class IKT, class VPT >
class BucketCache {
public:

	typedef  BKT TBucketKey;
	typedef  IKT TValueKey;

	typedef  VPT  TValuePtr;

	virtual ~BucketCache() throw(){};

	class BucketStorage;

	class Bucket : public RefCountingPointee{

		public:

			virtual ~Bucket(){};

			class ItemEntry : public RefCountingPointee {
				public:

					ItemEntry(const IKT& key, const VPT& ptrValue):key(key),ptrValue(ptrValue){};

					operator VPT(){ return ptrValue;};
					operator const VPT&()const { return ptrValue;};
					const VPT& getValue()const { return ptrValue; }

					const IKT& getKey()const {return key; }

					void setValue(const VPT& ptrValue){
						this->ptrValue=ptrValue;
					}

				protected:
				IKT  key;
				VPT  ptrValue;
			};

			typedef typename IAS_DFT_FACTORY<ItemEntry>::RefCountingPtr ItemEntryPtr;
			typedef  _BucketMap<IKT,ItemEntryPtr> ItemMap;

			void createOrUpdate(const IKT& key, const VPT &ptrValue){

				IAS_TRACER;

				if(setUpdatedEntres.empty())
					iVersion++;

				if(hmItems.count(key) == 0){
					ItemEntryPtr ptrItemEntry(IAS_DFT_FACTORY<ItemEntry>::Create(key,ptrValue));
					hmItems[key]=ptrItemEntry;
					setUpdatedEntres.insert(ptrItemEntry);
				}else{
					ItemEntry *pItemEntry=hmItems[key];
					pItemEntry->setValue(ptrValue);
					setUpdatedEntres.insert(pItemEntry);
				}

			}

			const VPT& at(const IKT& key){
				IAS_TRACER;
				if(hmItems.count(key) == 0)
					IAS_THROW(ItemNotFoundException(String("Item:")+(String)key));


				return hmItems[key]->getValue();
			}

			ItemEntry& operator[](const IKT key){return at(key);}


			typedef typename ItemMap::const_iterator const_iterator;

			const_iterator begin()const{ return hmItems.begin(); }
			const_iterator end()const{ return hmItems.end(); }

			typedef std::set<ItemEntry*> ItemEntrySet;

			typename ItemEntrySet::const_iterator beginUpdated()const{ return setUpdatedEntres.begin(); }
			typename ItemEntrySet::const_iterator endUpdated()const{ return setUpdatedEntres.end(); }

			Bucket(const BKT& id, size_t iVersion=0):id(id),iVersion(iVersion){};

			const BKT& getID()const {return id;};
			size_t     getVersion()const{ return iVersion;}
			void       clearUpdatedList(){ setUpdatedEntres.clear(); }
			bool       isChanged()const{ return !setUpdatedEntres.empty(); }

		protected:

	    BKT     id;
	    size_t  iVersion;
		ItemMap hmItems;
		ItemEntrySet                 setUpdatedEntres;

		friend class BucketCache<BKT,IKT,VPT>::BucketStorage;
	};

	typedef typename ::IAS::MemoryManagerFactory<Bucket>::RefCountingPtr BucketPtr;

	typedef _BucketMap<BKT,BucketPtr> BucketMap;


	class BucketStorage{
		public:
		virtual ~BucketStorage(){};

		virtual void createBucket(Bucket* pBucket){
			IAS_THROW(InternalException("BucketStorage::createBucket not implemented"));
		};

		virtual void fetchBucket(Bucket* pBucket){
			IAS_THROW(InternalException("BucketStorage::fetchBucket not implemented"));
		};

		virtual void fetchBucketItems(Bucket* pBucket, size_t iSinceVersion = 0){
			IAS_THROW(InternalException("BucketStorage::fetchBucketItems not implemented"));
		};

		virtual void updateBucket(Bucket* pBucket){
			IAS_THROW(InternalException("BucketStorage::updateBucket not implemented"));
		};

		virtual void deleteBucket(Bucket* pBucket){
			IAS_THROW(InternalException("BucketStorage::deleteBucket not implemented"));
		};

		virtual void createOrUpdateBucketItem(Bucket* pBucket,const typename Bucket::ItemEntry* pValue){
			IAS_THROW(InternalException("BucketStorage::createOrUpdateBucketItem not implemented"));
		};

		protected:
			void insertBucketItemImpl(Bucket* pBucket, const IKT& key, const VPT &ptrValue){
				pBucket->hmItems[key]=IAS_DFT_FACTORY<typename Bucket::ItemEntry>::Create(key,ptrValue);
			}

			void setVersionImpl(Bucket* pBucket, size_t iVersion){
				pBucket->iVersion=iVersion;
			}
	};

	/*************************************************************************************/
	BucketPtr createBucket(const BKT& id){
		IAS_TRACER;

		Mutex::Locker locker(mutex);

		if(pRecentMap->count(id) > 0 || pOldMap->count(id) > 0)
			IAS_THROW(AlreadyExists(String("Bucket already exists:")+(String)id ));


		swapMapsIfNeeded();

		BucketPtr pNew = IAS_DFT_FACTORY<Bucket>::Create(id);

		if(pStorage)
			pStorage->createBucket(pNew);

		return pNew;
	}

	/*************************************************************************************/
	BucketPtr getBucket(const BKT& id){
		IAS_TRACER;

		Mutex::Locker locker(mutex);

		BucketPtr ptrResult;
		{
			typename BucketMap::iterator it=pRecentMap->find(id);
			if(it != pRecentMap->end()){
				ptrResult = it->second;
				pRecentMap->erase(it);
			}

		}

		{
			typename BucketMap::iterator it=pOldMap->find(id);
			if(it != pOldMap->end()){
				ptrResult = it->second;
				pOldMap->erase(it);
			}

		}

		if(!ptrResult && !pStorage)
			IAS_THROW(ItemNotFoundException(String("Bucket, id=")+(String)id));

		if(!ptrResult)
			ptrResult = IAS_DFT_FACTORY<Bucket>::Create(id);

		size_t iVersion=ptrResult->getVersion();

		if(pStorage)
			try{
				pStorage->fetchBucket(ptrResult);
				if(ptrResult->getVersion() > iVersion)
					pStorage->fetchBucketItems(ptrResult,iVersion);
			}catch(ItemNotFoundException& e){
				IAS_THROW(ItemNotFoundException(String("Bucket, id=")+(String)id+e.getInfo()));
			}catch(Exception& e){
				IAS_THROW(Exception(String("Problem fetching bucket content, id=")+(String)id+e.getInfo()));
			}

		return ptrResult;
	}

	void storeBucket(const BucketPtr& ptrBucket){
		IAS_TRACER;

		if(pStorage && ptrBucket->isChanged())
			//try
		{

				pStorage->updateBucket(ptrBucket);

				for(typename Bucket::ItemEntrySet::const_iterator it=ptrBucket->beginUpdated();
					it != ptrBucket->endUpdated(); it++)
					pStorage->createOrUpdateBucketItem(ptrBucket,*it);


			//}catch(Exception& e){
			//	IAS_THROW(Exception(String("Problem updating bucket, id=")+(String)ptrBucket->getID()+e.getName()+e.getInfo()));
			//
				}

		ptrBucket->clearUpdatedList();
		(*pRecentMap)[ptrBucket->getID()]=ptrBucket;
	}


	/*************************************************************************************/
	void deleteBucket(const BKT& id){
		IAS_TRACER;

		Mutex::Locker locker(mutex);

		BucketPtr ptrResult;
		{
			typename BucketMap::iterator it=pRecentMap->find(id);
			if(it != pRecentMap->end()){
				ptrResult = it->second;
				pRecentMap->erase(it);
			}

		}

		{
			typename BucketMap::iterator it=pOldMap->find(id);
			if(it != pOldMap->end()){
				ptrResult = it->second;
				pOldMap->erase(it);
			}

		}

		if(!ptrResult)
			ptrResult = IAS_DFT_FACTORY<Bucket>::Create(id);

		if(pStorage)
			pStorage->deleteBucket(ptrResult);

	}

	class AutoReturn : public BucketPtr {
		public:

		AutoReturn():pBucketCache(0){};

		AutoReturn(const BucketPtr& ptrBucket, BucketCache* pBucketCache):
			BucketPtr(ptrBucket),pBucketCache(pBucketCache){};

		void forget(){ pBucketCache=NULL; this->unset(); }

		void set(const BucketPtr& ptrBucket, BucketCache* pBucketCache){

			if(this->pBucketCache)
				this->pBucketCache->storeBucket(*this);

			BucketPtr::operator=(ptrBucket);
			this->pBucketCache=pBucketCache;
		};

		void returnNow(){
			if(pBucketCache)
				pBucketCache->storeBucket(*this);
			forget();
		}

		~AutoReturn(){
			returnNow();
		}

		private:
			BucketCache* pBucketCache;
	};
	/*************************************************************************************/

protected:
	BucketCache(BucketStorage *pStorage = 0, int iMaxSize=10):
		pRecentMap(&hmBucketsOne),
		pOldMap(&hmBucketsTwo),
		iMaxSize(iMaxSize),
		pStorage(pStorage){};

	void setMaxSize(size_t iMaxSize){
		this->iMaxSize=iMaxSize;
		swapMapsIfNeeded();
	}

	void setStorage(BucketStorage* pStorage){
		IAS_TRACER;
		if(pRecentMap->size() > 0 || pOldMap->size() > 0)
			IAS_THROW(InternalException("Cannot change BucketStorage when items have been already added to a cache."));

		this->pStorage=pStorage;
	}

private:

	BucketMap  hmBucketsOne;
	BucketMap  hmBucketsTwo;

	typedef BucketMap* BucketMapPtr;

	BucketMapPtr pRecentMap;
	BucketMapPtr pOldMap;

	BucketStorage* pStorage;

	void swapMapsIfNeeded(){
		IAS_TRACER;

		if(pRecentMap->size() > iMaxSize){
			IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(), "swapping");
			BucketMapPtr tmp=pRecentMap;
			pRecentMap=pOldMap;
			pOldMap=tmp;
			pRecentMap->clear();
		}

	}

	Mutex mutex;
	size_t  iMaxSize;
	friend class Factory<BucketCache>;
};

template <class VPT>
class StandardBucketCache : public BucketCache<String,String,VPT>{
public:
	StandardBucketCache(typename StandardBucketCache::BucketStorage* pStorage=0, int iMaxSize=10):
		BucketCache<String,String,VPT>(pStorage,iMaxSize){};
};

/*************************************************************************/
}
}

#endif /* _IAS_Cache_BucketCache_H_ */
