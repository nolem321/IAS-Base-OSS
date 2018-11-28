/*
 * File: IAS-CommonLib/src/commonlib/memory/mm/SimpleListMemoryManager.cpp
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
#include "SimpleListMemoryManager.h"


#include <org/invenireaude/qsystem/stats/DataFactory.h>
#include <org/invenireaude/qsystem/stats/MemorySlot.h>
#include <org/invenireaude/qsystem/stats/Sample.h>

using namespace org::invenireaude::qsystem;

namespace IAS {
namespace QS {
namespace SHM {
namespace MM {

/*************************************************************************/
SimpleListMemoryManager::SimpleListMemoryManager(void *pStart, size_t iSize):
IAS::SimpleListMemoryManager(pStart,iSize){}
/*************************************************************************/
SimpleListMemoryManager::SimpleListMemoryManager(void *pStart):
IAS::SimpleListMemoryManager(pStart){}
/*************************************************************************/
SimpleListMemoryManager::~SimpleListMemoryManager()throw(){}
/*************************************************************************/
// TODO move to CommonLib
static inline int _backetNo(long iSize, int iMax){
	int iResult=0;
	iSize>>=6;
	while(iSize || iResult >= iMax){
		iSize>>=1;
		iResult++;
	}
	return iResult;
}

/*************************************************************************/
static void _fillTSR(stats::Sample* dmSample, TimeSamplesResults& tsr){
    dmSample->setMin(tsr.iMin/1000);
    dmSample->setMax(tsr.iMax/1000);
    dmSample->setAvg(tsr.iNumSamples ? tsr.iTotal/1000 / tsr.iNumSamples : 0);
    dmSample->setTotal(tsr.iTotal/1000);
    dmSample->setNum(tsr.iNumSamples);
}
/*************************************************************************/
stats::Ext::MemoryManagerPtr SimpleListMemoryManager::getStatistics() const{

  stats::Ext::MemoryManagerPtr dmMemoryManager(stats::DataFactory::GetInstance()->createMemoryManager());

	Mutex::Locker locker(pInfo->mutex);

	long tFreeBuckets[32];
	bzero(tFreeBuckets,sizeof(long)*32);

	long tFreeContinous[32];
	bzero(tFreeContinous,sizeof(long)*32);

	long tAllocBuckets[32];
	bzero(tAllocBuckets,sizeof(long)*32);

	long iFreeBuckets=0;
	long iFreeContinous=0;
	long iAllocBuckets=0;

	long iFreeTotal=0;
	long iAllocTotal=0;

  dmMemoryManager->setEntries(pInfo->iNumEntries);
  dmMemoryManager->setBucketSize(sizeof(Entry));

	long iContinous=0;
	for(Entry* current=pInfo->head;
			current->next!=pInfo->head;
			current=current->next){
		if(current->isFree()){
			iContinous+=current->getSize();
			iFreeTotal+=current->getSize();
			tFreeBuckets[_backetNo(current->iSize,32)]++;
			iFreeBuckets++;

		}else{
			tAllocBuckets[_backetNo(-(current->iSize),32)]++;
			if(iContinous)
				tFreeContinous[_backetNo(iContinous,32)]++;
			iAllocTotal+=current->getSize();
			iAllocBuckets++;
			iFreeBuckets++;
			iContinous=0;
		}
	}

	for(int i=0;(1L<<(i+5))<=(iAllocTotal+iFreeTotal);i++){
      stats::MemorySlot *dmMemorySlot = dmMemoryManager->createSlots();
      dmMemorySlot->setSize((1L<<(i+6)));
      dmMemorySlot->setFree(tFreeBuckets[i]);
      dmMemorySlot->setCfree(tFreeContinous[i]);
      dmMemorySlot->setAllocated(tAllocBuckets[i]);
  }


  dmMemoryManager->setTotalAllocated((long)iAllocTotal*sizeof(Entry));
  dmMemoryManager->setTotalSize(sizeof(Entry)*(iAllocTotal+iFreeTotal));
  dmMemoryManager->setFragmentationPct((long)(100*iFreeContinous/iFreeBuckets));

  dmMemoryManager->setAllocated((long)pInfo->iAllocated*sizeof(Entry));
  dmMemoryManager->setHighWater((long)iAllocTotal*sizeof(Entry));

  _fillTSR(dmMemoryManager->createWaits(), pInfo->tsrMutexWaits);
  _fillTSR(dmMemoryManager->createAllocations(), pInfo->tsrAllocations);
  _fillTSR(dmMemoryManager->createSearches(), pInfo->tsrSearches);
  _fillTSR(dmMemoryManager->createSearchesNoSplit(), pInfo->tsrSearchesNoSplit);

  return dmMemoryManager;
}
/*************************************************************************/

}
}
}
}
