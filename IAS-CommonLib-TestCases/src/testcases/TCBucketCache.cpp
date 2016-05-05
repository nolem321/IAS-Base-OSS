/*
 * File: IAS-CommonLib-TestCases/src/testcases/TCBucketCache.cpp
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
#include "commonlib/commonlib.h"

#include "commonlib/caches/BucketCache.h"

#include "TCBucketCache.h"

#include<stdlib.h>

namespace IAS {
namespace TCT {

TCBucketCache::TCBucketCache(TestSuite* pTestSuite):theTestRunner(this) {
	IAS_TRACER;
	init(pTestSuite);

}

TCBucketCache::~TCBucketCache() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void TCBucketCache::init(TestSuite* pTestSuite) {
	IAS_TRACER;
	theTestRunner.addCase("ALL",&::IAS::TCT::TCBucketCache::caseALL);
	TestUnit::init("TCBucketCache",&theTestRunner,pTestSuite);
}
/*************************************************************************/

class CacheValue: public RefCountingPointee , public String{
public:
	CacheValue(int iValue):String(TypeTools::IntToString(iValue).c_str()){
		TheNumInstances++;
	};

	virtual ~CacheValue(){
		IAS_TRACER;
		IAS_LOG(IAS::LogLevel::INSTANCE.isDetailedInfo(), this->c_str());
		TheNumInstances--;
	}

	static int TheNumInstances;
};

int CacheValue::TheNumInstances(0);

typedef IAS_DFT_FACTORY<CacheValue>::RefCountingPtr ValuePtr;
typedef Cache::StandardBucketCache<ValuePtr> Cache;

/*************************************************************************/

class BucketStorage : public Cache::BucketStorage {
	public:
	virtual ~BucketStorage(){};

	virtual void createBucket(Cache::Bucket* pBucket){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE create Bucket:"<<pBucket->getID());
	};

	virtual void fetchBucket(Cache::Bucket* pBucket){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE fetch Bucket:"<<pBucket->getID());

		if(pBucket->getID().compare(info.keyBucket)==0){
			setVersionImpl(pBucket,info.iNewVersion);
		}
	};

	virtual void fetchBucketItems(Cache::Bucket* pBucket, size_t iSinceVersion = 0){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE fetch items, Bucket:"<<pBucket->getID());
		if(pBucket->getID().compare(info.keyBucket)==0 && pBucket->getVersion() == info.iNewVersion){
			insertBucketItemImpl(pBucket,info.keyValue,info.ptrValue);
		}
	};

	virtual void updateBucket(Cache::Bucket* pBucket){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE update Bucket:"<<pBucket->getID());
	};

	virtual void deleteBucket(Cache::Bucket* pBucket){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE delete Bucket:"<<pBucket->getID());
	};

	virtual void createOrUpdateBucketItem(Cache::Bucket* pBucket,const Cache::Bucket::ItemEntry* pValue){
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"STORE create or update items, Bucket:"<<pBucket->getID()<<","<<pValue->getKey());
	};

	struct UpdateThisBucket{
		size_t iNewVersion;
		Cache::TBucketKey     keyBucket;
		Cache::TValueKey      keyValue;
		Cache::TValuePtr      ptrValue;
	};

	UpdateThisBucket info;
};
static const int CNumBuckets = 50;
/*************************************************************************/
void TCBucketCache::caseALL() {
	IAS_TRACER;

	//LogLevel::INSTANCE.bIsInfo=true;

	IAS_DFT_FACTORY<BucketStorage>::PtrHolder ptrBucketStorage(IAS_DFT_FACTORY<BucketStorage>::Create());

	IAS_DFT_FACTORY<Cache>::PtrHolder ptrCache(IAS_DFT_FACTORY<Cache>::Create(ptrBucketStorage.getPointer()));

	for(int iBuckets=0;iBuckets<CNumBuckets;iBuckets++){
		String strBucket(String("Bucket_")+TypeTools::IntToString(iBuckets).c_str());

		{
			Cache::AutoReturn ptrBucket(ptrCache->createBucket(strBucket),ptrCache);

			for(int iValues=0;iValues<iBuckets*2;iValues++) {
				String strItemKey(String("IK_")+TypeTools::IntToString(iValues).c_str());

				IAS_LOG(LogLevel::INSTANCE.isInfo(),"Will create: "<<strItemKey<<" for :"<<strBucket);

				ptrBucket->createOrUpdate(strItemKey,IAS_DFT_FACTORY<CacheValue>::Create(iValues));

				if(iValues % 3 == 0)
					ptrBucket->createOrUpdate(strItemKey,IAS_DFT_FACTORY<CacheValue>::Create(iValues*1000));
			}

		}

		try{
			ptrCache->createBucket(strBucket);
			IAS_THROW(BadUsageException("Exception expected 1."));
		}catch(AlreadyExists& e){}

		Cache::AutoReturn ptrBucket(ptrCache->getBucket(strBucket), ptrCache);
		if(iBuckets % 8 == 0)
			ptrBucket.forget();

	}


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Instances in cache:"<<CacheValue::TheNumInstances<<", fetching ..")

	ptrBucketStorage->info.iNewVersion=3;
	ptrBucketStorage->info.keyBucket="Bucket_30";
	ptrBucketStorage->info.keyValue="NewItem";
	ptrBucketStorage->info.ptrValue=IAS_DFT_FACTORY<CacheValue>::Create(1234567890);

	for(int iBuckets=0;iBuckets<CNumBuckets;iBuckets++){

		String strBucket(String("Bucket_")+TypeTools::IntToString(iBuckets).c_str());

		try{
			Cache::AutoReturn ptrBucket(ptrCache->getBucket(strBucket), ptrCache);

			if(strBucket.compare(ptrBucket->getID()) != 0)
				IAS_THROW(BadUsageException(strBucket + " does not match."));

			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Got: "<<strBucket);

			bool bFound=false;
			for(Cache::Bucket::const_iterator it=ptrBucket->begin();
					it != ptrBucket->end(); it++){

				IAS_LOG(LogLevel::INSTANCE.isInfo(),strBucket<<"["<<it->first<<"]"<<(!it->second ? "!=" : "==")<<*(ValuePtr)(*it->second));

				if(it->first.compare(ptrBucketStorage->info.keyValue) == 0 &&
							((ValuePtr)(*it->second))->compare(ptrBucketStorage->info.ptrValue->c_str()) == 0)
						bFound=true;

			}

			if(ptrBucket->getID().compare(ptrBucketStorage->info.keyBucket) == 0 && !bFound){
				IAS_THROW(BadUsageException(strBucket + " new item expected."));
			}

			if(iBuckets % 10 == 5)
					ptrBucket->createOrUpdate("NewItemForFiths",IAS_DFT_FACTORY<CacheValue>::Create(55555));

		}catch(ItemNotFoundException& e){
			IAS_LOG(LogLevel::INSTANCE.isInfo(),"Not found: "<<strBucket<<", hope it is ok.");
		}

	}


	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Instances in cache:"<<CacheValue::TheNumInstances)

	ptrCache=0;
	ptrBucketStorage=0;

	if(CacheValue::TheNumInstances)
		IAS_THROW(BadUsageException(String("Some instances left:")+TypeTools::IntToString(CacheValue::TheNumInstances)));
}
/*************************************************************************/


}
}
