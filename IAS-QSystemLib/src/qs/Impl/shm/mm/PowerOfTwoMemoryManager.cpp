/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/PowerOfTwoMemoryManager.cpp
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
#include "PowerOfTwoMemoryManager.h"

#include <org/invenireaude/qsystem/stats/DataFactory.h>
#include <org/invenireaude/qsystem/stats/MemorySlot.h>
#include <org/invenireaude/qsystem/stats/Sample.h>

using namespace org::invenireaude::qsystem;


namespace IAS {
namespace QS {
namespace SHM {
namespace MM {

/*************************************************************************/
PowerOfTwoMemoryManager::PowerOfTwoMemoryManager(void *pStart, size_t iSize):
IAS::PowerOfTwoMemoryManager(pStart,iSize){}
/*************************************************************************/
PowerOfTwoMemoryManager::PowerOfTwoMemoryManager(void *pStart):
IAS::PowerOfTwoMemoryManager(pStart){}
/*************************************************************************/
PowerOfTwoMemoryManager::~PowerOfTwoMemoryManager()throw(){}
/*************************************************************************/
static void _fillTSR(stats::Sample* dmSample, TimeSamplesResults& tsr){
    dmSample->setMin(tsr.iMin/1000);
    dmSample->setMax(tsr.iMax/1000);
    dmSample->setAvg(tsr.iNumSamples ? tsr.iTotal/1000 / tsr.iNumSamples : 0);
    dmSample->setTotal(tsr.iTotal/1000);
    dmSample->setNum(tsr.iNumSamples);
}
/*************************************************************************/
stats::Ext::MemoryManagerPtr PowerOfTwoMemoryManager::getStatistics() const{

	IAS_TRACER;

  stats::Ext::MemoryManagerPtr dmMemoryManager(stats::DataFactory::GetInstance()->createMemoryManager());

	Mutex::Locker locker(pInfo->mutex);

	size_t iAllocatedMem=0;
	size_t iMemTotal=pInfo->iSegments*pInfo->iSegmentSize;
	int    iAllocatedCnt=0;

	int    tBucketsBlocks[64];
	int    tBucketsSegs[64];
	int    tBucketsSegsFull[64];

	bzero(tBucketsBlocks,   sizeof(int)*64);
	bzero(tBucketsSegs,     sizeof(int)*64);
	bzero(tBucketsSegsFull, sizeof(int)*64);

	int iUsedSegments=0;

	for(int iIdx=0; iIdx<pInfo->iSegments; iIdx++){

		size_t iAllocated=pInfo->pSegments[iIdx].getAllocated();
		int    iBucket=pInfo->pSegments[iIdx].getBucket();

		if(iAllocated){
			iAllocatedMem+=iAllocated*(1L<<iBucket);
			iAllocatedCnt+=iAllocated;
			tBucketsBlocks[iBucket]+=iAllocated;
			tBucketsSegs[iBucket]++;
			if(pInfo->pSegments[iIdx].isFull())
				tBucketsSegsFull[iBucket]++;
			iUsedSegments++;
		}
	}

	iAllocatedMem<<=pInfo->iLgBaseSize;

	//os<<"  Allocated: "<<(long)(iUsedSegments)<<"("<<100*iUsedSegments/pInfo->iSegments<<"%) segments of "<<(long)(pInfo->iSegments)<<" total."<<std::endl;

  dmMemoryManager->setTotalAllocated((long)(iAllocatedMem));
  dmMemoryManager->setTotalSize(iMemTotal);

  dmMemoryManager->setTotalSegments((long)(pInfo->iSegments));
  dmMemoryManager->setAllocatedSegments(iUsedSegments);

	for(int iIdx=0; iIdx<pInfo->iBuckets; iIdx++){
      stats::MemorySlot *dmMemorySlot = dmMemoryManager->createSlots();
      dmMemorySlot->setSize((1L<<(iIdx+pInfo->iLgBaseSize)));
      dmMemorySlot->setFree(tBucketsBlocks[iIdx]);
      dmMemorySlot->setCfree(tBucketsSegs[iIdx]);
      dmMemorySlot->setAllocated(tBucketsSegsFull[iIdx]);
  }

  _fillTSR(dmMemoryManager->createWaits(), pInfo->tsrMutexWaits);
  _fillTSR(dmMemoryManager->createAllocations(), pInfo->tsrAllocations);

  return dmMemoryManager;
}
/*************************************************************************/
}
}
}
}