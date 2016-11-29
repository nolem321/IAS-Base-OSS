/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/PersistentCacheStorage.cpp
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
#include "PersistentCacheStorage.h"
#include <qs/log/LogLevel.h>

#include <qs/workers/proc/GlobalContext.h>
#include <qs/workers/proc/ProgramProvider.h>
#include <qs/workers/proc/prog/DefaultResultHandler.h>

#include <org/invenireaude/qsystem/workers/cache/Bucket.h>
#include <org/invenireaude/qsystem/workers/cache/Item.h>
#include <org/invenireaude/qsystem/workers/cache/DataFactory.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

using namespace org::invenireaude::qsystem::workers::cache;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Cache {

/*************************************************************************/
PersistentCacheStorage::PersistentCacheStorage(const String& strPackage, class GlobalContext* pGlobalContext):
		strPackage(strPackage){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"CacheStorage using: "<<strPackage);

	ptrProgramSet=IAS_DFT_FACTORY<Prog::ProgramSet>::Create(pGlobalContext->getDataFactory());

	ptrProgramSet->setResultHandler(IAS_DFT_FACTORY<Proc::Prog::DefaultResultHandler>::Create(pGlobalContext->getDataFactory()));

	//Same as for SPS DataStore
	//TODO error handling try{} catch null problems
	//TODO error handling when sql specification problem error
	//TODO error handling when exception in constructor IAS::StandardFactory<IAS::QS::Workers::Proc::Logic::SPS::ProcessCache>::Create () at ../IAS-CommonLib/src/commonlib/memory/Factory.h:78

	try{
		pGlobalContext->getProgramProvider()->load(strPackage+"::createBucket",ptrProgramSet);
		pGlobalContext->getProgramProvider()->load(strPackage+"::updateBucket",ptrProgramSet);
		pGlobalContext->getProgramProvider()->load(strPackage+"::fetchBucket",ptrProgramSet);
		pGlobalContext->getProgramProvider()->load(strPackage+"::deleteBucket",ptrProgramSet);

		pGlobalContext->getProgramProvider()->load(strPackage+"::fetchBucketItems",ptrProgramSet);
		pGlobalContext->getProgramProvider()->load(strPackage+"::createOrUpdateBucketItem",ptrProgramSet);

	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isError(),e.toString());
	}
}
/*************************************************************************/
PersistentCacheStorage::~PersistentCacheStorage() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void PersistentCacheStorage::createBucket(WorkerCache::Bucket* pBucket){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Bucket: "<<pBucket->getID());

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());
	dmBucket->setVersion(pBucket->getVersion());

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::createBucket",dmContext,dmBucket);

}
/*************************************************************************/
void PersistentCacheStorage::fetchBucket(WorkerCache::Bucket* pBucket){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Bucket: "<<pBucket->getID()<<", vers="<<pBucket->getVersion());

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::fetchBucket",dmContext,dmBucket);

	if(!dmBucket->isSetVersion())
		//TODO better exception
		IAS_THROW(ItemNotFoundException(pBucket->getID()));


	setVersionImpl(pBucket,dmBucket->getVersion());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"New version = "<<pBucket->getVersion());

}
/*************************************************************************/
void PersistentCacheStorage::fetchBucketItems(WorkerCache::Bucket* pBucket, size_t iSinceVersion){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Bucket: "<<pBucket->getID());

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());
	dmBucket->setVersion(iSinceVersion);

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::fetchBucketItems",dmContext,dmBucket);

	const Ext::ItemList& lstItems(dmBucket->getItemsList());
	for(int iIdx=0; iIdx<lstItems.size(); iIdx++){
		const Item* dmItem=lstItems.at(iIdx);
		insertBucketItemImpl(pBucket, dmItem->getKey(), dmItem->getValue());
	}
}
/*************************************************************************/
void PersistentCacheStorage::updateBucket(WorkerCache::Bucket* pBucket){
	IAS_TRACER;

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());
	dmBucket->setVersion(pBucket->getVersion());

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::updateBucket",dmContext,dmBucket);
}
/*************************************************************************/

void PersistentCacheStorage::deleteBucket(WorkerCache::Bucket* pBucket){
	IAS_TRACER;

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());
	dmBucket->setVersion(pBucket->getVersion());

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::deleteBucket",dmContext,dmBucket);

}
/*************************************************************************/

void PersistentCacheStorage::createOrUpdateBucketItem(WorkerCache::Bucket* pBucket,
		const WorkerCache::Bucket::ItemEntry* pValue){
	IAS_TRACER;

	Ext::BucketPtr dmBucket(DataFactory::GetInstance()->createBucket());

	dmBucket->setId(pBucket->getID());
	dmBucket->setVersion(pBucket->getVersion());

	Item *dmItem=dmBucket->createItems();

	dmItem->setKey(pValue->getKey());
	dmItem->setValue(pValue->getValue()->duplicate());

	::org::invenireaude::qsystem::workers::Ext::ContextPtr dmContext(::org::invenireaude::qsystem::workers::DataFactory::GetInstance()->createContext());
	ptrProgramSet->execute(strPackage+"::createOrUpdateBucketItem",dmContext,dmBucket);

}
/*************************************************************************/
}
}
}
}
}
