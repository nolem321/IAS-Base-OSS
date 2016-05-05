/*
 * File: IAS-QSystemLib/src/qs/workers/proc/cache/CacheFactory.cpp
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
#include "CacheFactory.h"
#include <qs/log/LogLevel.h>


#include <org/invenireaude/qsystem/workers/cache/Cache.h>
#include <org/invenireaude/qsystem/workers/cache/PersistentCache.h>
#include <org/invenireaude/qsystem/workers/cache/LocalCache.h>
#include <org/invenireaude/qsystem/workers/cache/DataFactory.h>


#include "CacheStore.h"
#include "../GlobalContext.h"

#include "PersistentCache.h"
#include "LocalCache.h"


using namespace ::org::invenireaude::qsystem::workers;


namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Cache {
/*************************************************************************/
static String _HackURI(const String& strSpecs) {
	//TODO some hacking for cache url ?
	return strSpecs;
}
/*************************************************************************/
void CacheFactory::CreateCaches(const ::org::invenireaude::qsystem::workers::cache::Specification* dmSpecification,
					   	 CacheStore *pCacheStore,
						 GlobalContext *pGlobalContext){
	IAS_TRACER;

	const cache::Ext::CacheList& lstCaches(dmSpecification->getCachesList());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Caches: "<<lstCaches.size());

	for(int iIdx=0;iIdx<lstCaches.size();iIdx++){

		const cache::Cache* pCache(lstCaches.at(iIdx));

		if(cache::DataFactory::GetInstance()->getLocalCacheType()->equals(pCache->getType())){

			pCacheStore->addCache(pCache->getName(),
					IAS_DFT_FACTORY<LocalCache>::Create(
							cache::DataFactory::GetInstance()->getLocalCacheType()->cast(pCache),
							pGlobalContext));

		}else if(cache::DataFactory::GetInstance()->getPersistentCacheType()->equals(pCache->getType())){

			pCacheStore->addCache(pCache->getName(),
						IAS_DFT_FACTORY<PersistentCache>::Create(
								cache::DataFactory::GetInstance()->getPersistentCacheType()->cast(pCache),
								pGlobalContext));

		}else{
			IAS_THROW(InternalException(pCache->getType()->getName()+"Unknown specification type."));
		}

	}

}
/*************************************************************************/

::org::invenireaude::qsystem::workers::cache::Ext::SpecificationPtr
 CacheFactory::CacheSpecsToDM(const String& strSpecs){
	IAS_TRACER;

	::org::invenireaude::qsystem::workers::cache::Ext::SpecificationPtr ptrResult;

	if(!strSpecs.empty() && strSpecs.find(':') == String::npos){

			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Reading:"<<strSpecs);

			DM::DataObjectPtr dm(DM::Tools::Formatter::LoadFile(strSpecs,
																cache::DataFactory::GetInstance()->getContaingDataFactory(),
																cache::DataFactory::GetInstance()->getSpecificationType()));

			ptrResult = cache::DataFactory::GetInstance()->getSpecificationType()->cast(dm);

		}else{

			URI uri(_HackURI(strSpecs));

			if(uri.getProtocol().compare("lcache") == 0){
				cache::Ext::LocalCachePtr ptrCache(cache::DataFactory::GetInstance()->getLocalCacheType()->createLocalCache());
				ptrCache->setName("default");
				ptrResult->setCaches(ptrCache);
			}else if(uri.getProtocol().compare("pcache") == 0){
				cache::Ext::PersistentCachePtr ptrPersistentCache(cache::DataFactory::GetInstance()->getPersistentCacheType()->createPersistentCache());
				ptrPersistentCache->setPackage(uri.getPath());//TOOD change / to ::
				ptrPersistentCache->setName("default");
				ptrResult->setCaches(ptrPersistentCache);
			}else {
				IAS_THROW(BadUsageException(uri.getProtocol()+" bad protocol name for cache."));
			}
	}

	return ptrResult;
}
/*************************************************************************/
}
}
}
}
}
