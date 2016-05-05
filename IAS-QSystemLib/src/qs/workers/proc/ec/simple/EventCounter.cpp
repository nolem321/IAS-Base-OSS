/*
 * File: IAS-QSystemLib/src/qs/workers/proc/ec/simple/EventCounter.cpp
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
#include "EventCounter.h"
#include <qs/log/LogLevel.h>
#include <commonlib/sys/fs/FileLock.h>

#include <org/invenireaude/qsystem/workers/Connection.h>

#include <org/invenireaude/qsystem/workers/ec/DataFactory.h>

#include "Data.h"

using namespace org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace EC {
namespace Simple {

/*************************************************************************/
EventCounter::EventCounter(const ::org::invenireaude::qsystem::workers::ec::SimpleEventCounter* dmParameters):
		pSamples(0),
		pKeys(0){
	IAS_TRACER;

	Data::Settings settings;

	strName = "EC.";
	strName +=  dmParameters->getConnection()->getLocation();

	settings.iMaxNumSamples = PrimeNumbers::GetNextGtEq(2*dmParameters->getSize());

	settings.iResetInterval = dmParameters->isSetResetInterval() ? dmParameters->getResetInterval() : 3600;

	settings.iKeyStorageSize = settings.iMaxNumSamples *
				(dmParameters->isSetAvgKeyLen() ? dmParameters->getAvgKeyLen() : 32);

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"EC Name: "<<strName);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Size:    "<<settings.iMaxNumSamples);

	SYS::FS::FileLock lock(String("/tmp/ias.qs.ec.")+strName+".lck");
	SYS::Locker locker(&lock);

	SharedMemoryFile::Descriptor descriptor;

	descriptor.setDomain(SharedMemoryFile::Descriptor::DM_SHARED_MEMORY);
	descriptor.setOpenMode(SharedMemoryFile::Descriptor::OM_CREATE_IF_NEEDED);

	descriptor.setName(strName);

	ptrShared=IAS_DFT_FACTORY< SharedContent<Data> >::Create(descriptor, settings);

	descriptor.setSize(sizeof(Data::Sample)*settings.iMaxNumSamples);

	descriptor.setName(strName+".s");
	ptrSamples  = IAS_DFT_FACTORY<SharedMemoryFile>::Create(descriptor);

	descriptor.setSize(settings.iKeyStorageSize);

	descriptor.setName(strName+".k");
	ptrKeys = IAS_DFT_FACTORY<SharedMemoryFile>::Create(descriptor);

	pData   = ptrShared->get();

	pSamples = static_cast<Data::Sample*>(ptrSamples->getAddress());
	pKeys = static_cast<char*>(ptrKeys->getAddress());
}
/*************************************************************************/
EventCounter::~EventCounter() throw(){
	IAS_TRACER;
}

/*************************************************************************/
void EventCounter::resetIfNeeded(long ts) {
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isDetailedInfo(),"reset ? "<<ts<<" at: "<<pData->tsVersion<<", interval="<<pData->settings.iResetInterval);

	if( pData->isEmpty() || ts >= pData->tsVersion + pData->settings.iResetInterval){
		pData->tsVersion = ts / pData->settings.iResetInterval *  pData->settings.iResetInterval ;
		pData->iKeyStorageUsed=0;
		pData->iNumSamples=0;
	}
}
/*************************************************************************/
void EventCounter::update(const String& strKey,	unsigned int iValue, long ts, ec::Ext::RecordPtr& dmOutput){

	IAS_TRACER;

	Mutex::Locker locker(pData->theMutex);

	resetIfNeeded(ts);

	Data::Sample* pSample;

	dmOutput = ec::DataFactory::GetInstance()->getRecordType()->createRecord();

	if(lookup(strKey,pSample)){

		pSample->tsUpdate=ts;

		Data::Record& record(pSample->record);

		record.iCount++;
		record.iTotal+=iValue;

		if(iValue > record.iMax)
			record.iMax=iValue;

		if(iValue < record.iMin)
			record.iMin=iValue;


		dmOutput->setTotal(record.iTotal);
		dmOutput->setAvg(record.iTotal/record.iCount);
		dmOutput->setMax(record.iMax);
		dmOutput->setMin(record.iMin);
		dmOutput->setCount(record.iCount);

	}else{

		if((pData->settings.iMaxNumSamples / 2) < pData->iNumSamples)
			IAS_THROW(BadUsageException("EventCounter: Simple HashTable is too small.")
					<<(pData->settings.iMaxNumSamples / 2) << " " << pData->iNumSamples)

		pData->iNumSamples++;

		pSample->tsUpdate=ts;
		pSample->iKeyOffset=appendKey(strKey);

		Data::Record& record(pSample->record);

		record.iCount=1;
		record.iTotal=iValue;
		record.iMax=iValue;
		record.iMin=iValue;

		dmOutput->setTotal(record.iTotal);
		dmOutput->setAvg(iValue);
		dmOutput->setMax(iValue);
		dmOutput->setMin(iValue);
		dmOutput->setCount(1);

	}

}
/*************************************************************************/
bool EventCounter::lookup(const String& strKey, Data::Sample* &pSample){
	IAS_TRACER;

	_Hash<String> hash;

	unsigned int iSampleIdx = hash(strKey) % pData->settings.iMaxNumSamples;

	int iCheck = pData->settings.iMaxNumSamples;

	do{
		iSampleIdx = iSampleIdx % pData->settings.iMaxNumSamples;
		pSample = pSamples + iSampleIdx;

		if(pSample->tsUpdate < pData->tsVersion)
			return false;

		if(strKey.compare(pKeys + pSample->iKeyOffset) == 0)
			return true;

		iSampleIdx++; //TODO better hashing.

	}while(iCheck-- > 0);


	IAS_THROW(InternalException("Infinite loop detected in EventCounter::lookup()."));

}

/*************************************************************************/
size_t EventCounter::appendKey(const String& strKey){
	IAS_TRACER;

	size_t iResult = pData->iKeyStorageUsed;

	char* tKeyStorageEnd  = pKeys + pData->iKeyStorageUsed;

	size_t iCount=0;
	size_t iLeft=pData->settings.iKeyStorageSize - pData->iKeyStorageUsed;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"appending: "<<strKey<<" at: "<<iResult);

	for(String::const_iterator it=strKey.begin();
			it != strKey.end(); it++){

		*tKeyStorageEnd++=*it;
		iCount++;
		iLeft--;

		if(iLeft == 0)
			IAS_THROW(BadUsageException("appendKey, key storage too small."));

	}

	*tKeyStorageEnd++=0;
    pData->iKeyStorageUsed += iCount+1;

	return iResult;
}
/*************************************************************************/
bool EventCounter::read(const String& strKey,
		  	  	  	  	org::invenireaude::qsystem::workers::ec::Ext::RecordPtr& dmRecord){
	IAS_TRACER;

	Mutex::Locker locker(pData->theMutex);

	Data::Sample* pSample;

	if(lookup(strKey,pSample)){

		dmRecord = ec::DataFactory::GetInstance()->getRecordType()->createRecord();

		Data::Record& record(pSample->record);

		dmRecord->setAvg(record.iTotal/record.iCount);
		dmRecord->setMax(record.iMax);
		dmRecord->setMin(record.iMin);
		dmRecord->setTotal(record.iTotal);
		dmRecord->setCount(record.iCount);

		return true;
	}


	return false;
}
/*
 * Linear search but it should not be used for large key sets, anyway.
 */
/*************************************************************************/
void EventCounter::readAll(DM::DataObjectList& dmRecordsList,
		 	 	 	 	   bool bReset){
	IAS_TRACER;

	Mutex::Locker locker(pData->theMutex);

	Data::Sample* pSample=pSamples;

	for(int iIdx = 0;
			iIdx < pData->settings.iMaxNumSamples;
			iIdx++, pSample++)
		if(pSample->tsUpdate > pData->tsVersion){

		ec::Ext::RecordPtr dmRecord = ec::DataFactory::GetInstance()->getRecordType()->createRecord();

		Data::Record& record(pSample->record);

		dmRecord->setKey(pKeys + pSample->iKeyOffset);
		dmRecord->setAvg(record.iTotal/record.iCount);
		dmRecord->setMax(record.iMax);
		dmRecord->setMin(record.iMin);
		dmRecord->setCount(record.iCount);

		IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"found: "<<pKeys + pSample->iKeyOffset<<" count: "<<record.iCount);

		dmRecordsList.add(dmRecord);
	}


	if(bReset){

		DateTime ts(true);

		pData->tsVersion       = ts;
		pData->iKeyStorageUsed = 0;
		pData->iNumSamples     = 0;
	}

}
/*************************************************************************/
}
}
}
}
}
}

