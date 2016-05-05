/*
 * File: IAS-QSystemMod-SPS/src/qs/workers/proc/logic/sps/CacheBase.cpp
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
#include "CacheBase.h"

#include "ProcessCacheEntry.h"

#include<qs/log/sps/LogLevel.h>

#include <org/invenireaude/qsystem/workers/sps/ProcessInstance.h>
#include <org/invenireaude/qsystem/workers/sps/ProcessArray.h>
#include <org/invenireaude/qsystem/workers/sps/DataFactory.h>

using namespace org::invenireaude::qsystem::workers::sps;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace Logic {
namespace SPS {

/*************************************************************************/
CacheBase::CacheBase()throw():
		pOld(&hmEntriesOne),
		pRecent(&hmEntriesTwo){
	IAS_TRACER;
}
/*************************************************************************/
CacheBase::~CacheBase() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void CacheBase::insert(ProcessCacheEntryPtr ptrCacheEntry){
	IAS_TRACER;

	const String& strKey=ptrCacheEntry->getProcessInstance()->getId();

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isError(),"key="<<strKey);

	Mutex::Locker locker(mutex);

	if( pOld->count(strKey) )
		pOld->erase(strKey);

	(*pRecent)[strKey]=ptrCacheEntry;

	if(pRecent->size() > CMaxEntries)
		swapNoLock();

	ptrCacheEntry.unset();
}
/*************************************************************************/
bool CacheBase::lookup(const String& strKey, ProcessCacheEntryPtr &ptrEntry){
	IAS_TRACER;

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isError(),"key="<<strKey);

	Mutex::Locker locker(mutex);

	if(hmEntriesOne.count(strKey) > 0) {
		ptrEntry=hmEntriesOne.at(strKey);
		hmEntriesOne.erase(strKey);
		return true;

	} else if(hmEntriesTwo.count(strKey) > 0){
		ptrEntry=hmEntriesTwo.at(strKey);
		hmEntriesTwo.erase(strKey);
		return true;
	}

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isError(),"not found !");

	return false;
}
/*************************************************************************/
void CacheBase::swapNoLock(){
	IAS_TRACER;


	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isError(),"cleaning up "<<pOld->size()<<" items.");

	pOld->clear();

	EntriesMap* pTmp=pRecent;
	pRecent=pOld;
	pOld=pTmp;

	IAS_LOG(IAS::QS::SPS::LogLevel::INSTANCE.isError(),"cache has "<<pOld->size()<<" recent items.");
}
/*************************************************************************/
}
}
}
}
}
}

