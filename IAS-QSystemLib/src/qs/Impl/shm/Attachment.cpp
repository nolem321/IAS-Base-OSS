/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Attachment.cpp
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
#include "Attachment.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "org/invenireaude/qsystem/System.h"
#include "org/invenireaude/qsystem/MemorySettings.h"
#include "org/invenireaude/qsystem/MemorySize.h"
#include "org/invenireaude/qsystem/QueueSettings.h"
#include "org/invenireaude/qsystem/SessionSettings.h"
#include "org/invenireaude/qsystem/ContentSettings.h"

#include <org/invenireaude/qsystem/stats/SystemStats.h>
#include <org/invenireaude/qsystem/stats/QueueStats.h>
#include <org/invenireaude/qsystem/stats/TopicStats.h>
#include <org/invenireaude/qsystem/stats/Sample.h>
#include <org/invenireaude/qsystem/stats/DataFactory.h>
#include <org/invenireaude/qsystem/stats/MemoryManager.h>
#include <org/invenireaude/qsystem/stats/MemoryStats.h>

#include "shared/System.h"
#include "shared/Queue.h"
#include "shared/QueueTable.h"
#include "shared/SessionTable.h"
#include "shared/ContentStorage.h"

#include "ContentManager.h"
#include "Connection.h"
#include "Administrator.h"

#include "admin/ActionDispatcher.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::PtrHolder  Attachment::TheMMSystemHeap;
IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::PtrHolder  Attachment::TheMMQueueData;
IAS_DFT_FACTORY< SHM::MM::PowerOfTwoMemoryManager >::PtrHolder  Attachment::TheMMApplicationData;

/*************************************************************************/
String Attachment::buildSHMName(const String& strName) {
	IAS_TRACER;
	String strSHMName("/QS.");
	strSHMName += strName;
	return strSHMName;
}
/*************************************************************************/
Attachment::Attachment(const ::org::invenireaude::qsystem::workers::Connection* dmConnection):
	strName(dmConnection->getHost()){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Attachment attaching to: ["<<strName<<"]");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");

	if(! !TheMMSystemHeap)
		IAS_THROW(InternalException("Attachment already created."))

	String strSHMName(buildSHMName(strName));

	SharedContent<Shared::System>::Descriptor sharedDescriptor;
	sharedDescriptor.setName(strSHMName);
	sharedDescriptor.setOpenMode(SharedContent<Shared::System>::Descriptor::OM_ATTACH);

	ptrShared=IAS_DFT_FACTORY< SharedContent<Shared::System> >::Create(sharedDescriptor,strName);

	if(!getShared()->systemVersion.isCompatible(Shared::System::CSoftwareVersion))
		IAS_THROW(InternalException(String("Incompatible versions: ")+
							               getShared()->systemVersion.toString()+" and "+
										   Shared::System::CSoftwareVersion.toString()));

	Locker locker(this);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"TODO - memory metrics!  ???????????????????????");

	/*
	 * Attachment heap.
	 */

	ptrSHMSystemHeap = attachSHM(strSHMName+".h",getShared()->shmSystemHeap.pAddress);
	TheMMSystemHeap=
			IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::Create(getShared()->shmSystemHeap.pAddress,
													   	   	   getShared()->shmSystemHeap.iSize);



	/*
	 * Queue data.
	 */

	ptrSHMQueueData = attachSHM(strSHMName+".q",getShared()->shmQueueData.pAddress);

	TheMMQueueData=
			IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::Create(getShared()->shmQueueData.pAddress,
					getShared()->shmQueueData.iSize);



	/*
	 * Application data.
	 */

	ptrSHMApplicationData = attachSHM(strSHMName+".a",getShared()->shmApplicationData.pAddress);

	TheMMApplicationData=
			IAS_DFT_FACTORY< SHM::MM::PowerOfTwoMemoryManager >::Create(getShared()->shmApplicationData.pAddress,
					getShared()->shmApplicationData.iSize);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Attachment attached to: ["<<strName<<"] and ready.");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");


	ptrContentManager=IAS_DFT_FACTORY< ContentManager >::Create(getContentStorage());
	ptrActionDispatcher=IAS_DFT_FACTORY< Admin::ActionDispatcher >::Create(this);
}
/*************************************************************************/
Attachment::Attachment(::org::invenireaude::qsystem::Ext::SystemPtr dmAttachment):
	strName(dmAttachment->getName()){
	IAS_TRACER;


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Attachment creation: ["<<strName<<"]");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");



	if(! !TheMMSystemHeap)
		IAS_THROW(InternalException("Attachment already created."))

	//TODO Validate name (length/characters etc.)

	String strSHMName(buildSHMName(strName));

	SharedContent<Shared::System>::Descriptor sharedDescriptor;
	sharedDescriptor.setName(strSHMName);
	sharedDescriptor.setOpenMode(SharedContent<Shared::System>::Descriptor::OM_CREATE_ALWAYS);

	ptrShared=IAS_DFT_FACTORY< SharedContent<Shared::System> >::Create(sharedDescriptor, strName);

	Locker locker(this);

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"TODO - memory metrics!  ???????????????????????");

	/*
	 * Attachment heap.
	 */

	ptrSHMSystemHeap = createSHM(strSHMName+".h",dmAttachment->getMemory()->getHeap()->getValue());
	getShared()->shmSystemHeap.pAddress=ptrSHMSystemHeap->getAddress();
	getShared()->shmSystemHeap.iSize=ptrSHMSystemHeap->getSize();

	TheMMSystemHeap=
			IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::Create(getShared()->shmSystemHeap.pAddress,
													   	   	   getShared()->shmSystemHeap.iSize);



	/*
	 * Queue data.
	 */

	ptrSHMQueueData = createSHM(strSHMName+".q",dmAttachment->getMemory()->getQueue()->getValue());
	getShared()->shmQueueData.pAddress=ptrSHMQueueData->getAddress();
	getShared()->shmQueueData.iSize=ptrSHMQueueData->getSize();

	TheMMQueueData=
			IAS_DFT_FACTORY< SHM::MM::SimpleListMemoryManager >::Create(getShared()->shmQueueData.pAddress,
					getShared()->shmQueueData.iSize);


	/*
	 * Application data.
	 */

	ptrSHMApplicationData = createSHM(strSHMName+".a",dmAttachment->getMemory()->getData()->getValue());
	getShared()->shmApplicationData.pAddress=ptrSHMApplicationData->getAddress();
	getShared()->shmApplicationData.iSize=ptrSHMApplicationData->getSize();

	TheMMApplicationData=
			IAS_DFT_FACTORY< SHM::MM::PowerOfTwoMemoryManager >::Create(getShared()->shmApplicationData.pAddress,
					getShared()->shmApplicationData.iSize);



	/*
	 * Create system heap.
	 */

	getShared()->pQueueTable =
				SystemAllocator<Shared::QueueTable>::Create(dmAttachment->getQueues()->getMaxQueues());

	getShared()->pSessionTable =
				SystemAllocator<Shared::SessionTable>::Create(dmAttachment->getSessions()->getMaxSessions());

	if(dmAttachment->getSessions()->isSetMaxOpenQueues())
		getSessionTable()->setMaxObjects(dmAttachment->getSessions()->getMaxOpenQueues());

	if(dmAttachment->getSessions()->isSetMaxRollbackSegment())
		getSessionTable()->setRollbackSegment(dmAttachment->getSessions()->getMaxRollbackSegment());

	/*
	 * Create application storage.
	 */

	getShared()->pContentStorage =
				QueueAllocator<Shared::ContentStorage>::Create(dmAttachment->getContent()->getMaxEntries());

	getShared()->pQueueTable->setDftQueueSize(dmAttachment->getQueues()->getDftSize());

	ptrActionDispatcher=IAS_DFT_FACTORY< Admin::ActionDispatcher >::Create(this);

	ptrActionDispatcher->dispatchWork(dmAttachment->getActionsList());

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Attachment created and ready.");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");

}
/*************************************************************************/
SharedMemoryFile* Attachment::createSHM(const String& strName,
									size_t iSize){
	IAS_TRACER;

	SharedContent<Shared::System>::Descriptor sharedDescriptor;
	sharedDescriptor.setName(strName);
	sharedDescriptor.setSize(iSize);
	sharedDescriptor.setOpenMode(SharedContent<Shared::System>::Descriptor::OM_CREATE_ALWAYS);

	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder   ptrSHMFile;

	ptrSHMFile=IAS_DFT_FACTORY< SharedMemoryFile >::Create(sharedDescriptor);

	return ptrSHMFile.pass();
}
/*************************************************************************/
SharedMemoryFile* Attachment::attachSHM(const String& strName, void *pAddress){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),strName<<" at: "<<((void*)pAddress));


	SharedContent<Shared::System>::Descriptor sharedDescriptor;
	sharedDescriptor.setName(strName);
	sharedDescriptor.setAddress(pAddress);
	sharedDescriptor.setOpenMode(SharedContent<Shared::System>::Descriptor::OM_ATTACH);

	IAS_DFT_FACTORY< SharedMemoryFile >::PtrHolder   ptrSHMFile;

	ptrSHMFile=IAS_DFT_FACTORY< SharedMemoryFile >::Create(sharedDescriptor);

	return ptrSHMFile.pass();
}
/*************************************************************************/
inline Shared::System* Attachment::getShared(){
	return ptrShared->get();
}
/*************************************************************************/
Attachment::Locker::Locker(Attachment* pAttachment):
	Mutex::Locker(pAttachment->getShared()->mutexSystem){
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"QS lock obtained.");
}
/*************************************************************************/
Attachment::Locker::~Locker(){
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"QS lock released.");
}
/*************************************************************************/
IAS::Allocator* Attachment::GetAllocatorForSystem(){
	IAS_TRACER;

	if(!TheMMSystemHeap)
			IAS_THROW(InternalException("Attachment allocator not initialized."))

	return TheMMSystemHeap;
}
/*************************************************************************/
IAS::Allocator* Attachment::GetAllocatorForQueueData(){
	IAS_TRACER;

	if(!TheMMQueueData)
			IAS_THROW(InternalException("Attachment allocator not initialized."))

	return TheMMQueueData;
}
/*************************************************************************/
IAS::Allocator* Attachment::GetAllocatorForApplicationData(){
	IAS_TRACER;

	if(!TheMMApplicationData)
			IAS_THROW(InternalException("Attachment allocator not initialized."))

	return TheMMApplicationData;
}
/*************************************************************************/
Shared::QueueTable* Attachment::getQueueTable(){
	IAS_TRACER;
	return getShared()->pQueueTable;
}
/*************************************************************************/
Shared::SessionTable* Attachment::getSessionTable(){
	IAS_TRACER;
	return getShared()->pSessionTable;
}
/*************************************************************************/
Shared::ContentStorage* Attachment::getContentStorage(){
	IAS_TRACER;
	return getShared()->pContentStorage;
}
/*************************************************************************/
API::Connection* Attachment::createConnection(const ::org::invenireaude::qsystem::workers::Connection* dmConnection){
	IAS_TRACER;

	//TODO (L) only one system allowed
	//should be one connection per system implementation or more when possible
	//and implementations

	if(strName.compare(dmConnection->getHost()) != 0)
		IAS_THROW(InternalException("TODO better exception - only one connection possible"));

	return IAS_DFT_FACTORY<QS::SHM::Connection>::Create(this);
}
/*************************************************************************/
void Attachment::dumpInfo(std::ostream& os){
	IAS_TRACER;
	os<<"Attachment: ["<<getShared()->sName<<"]"<<std::endl;
	TheMMSystemHeap->printToStream(os);
	TheMMQueueData->printToStream(os);
	TheMMApplicationData->printToStream(os);

	os<<"Topics:"<<std::endl;
	{
		for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Topic);
				it != getQueueTable()->end(); it++) {

			Shared::Queue::Stats stats;
			(*it)->getStats(stats);

			os<<"T: "<<(*it)->getName()<<", num_msgs = "<<(*it)->getNumMsgs()<<", max= "<<stats.iMaxNumMsgs<<", handlers="<<(*it)->getUsageCount()<<((*it)->getRemovePendingState()?" remove pending":"")<<std::endl;

			os<<"   Puts:  "<<stats.tsrPut<<std::endl;
			os<<"   Gets:  "<<stats.tsrGet<<std::endl;
			os<<"   Waits: "<<stats.tsrMutexWait<<std::endl;

			for(Shared::Queue* pCursor=(*it)->getSubscriptionList();
					(*it) != pCursor;
					pCursor = pCursor->getSubscriptionList()) {
				os<<"          - "<<pCursor->getName()<<" = "<<pCursor->getNumMsgs()<<std::endl;
			}
		}
	}

	os<<"Queues:"<<std::endl;
	{
		for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Queue);
					it != getQueueTable()->end(); it++) {

			Shared::Queue::Stats stats;
			(*it)->getStats(stats);

			os<<"Q: "<<(*it)->getName()<<", num_msgs = "<<(*it)->getNumMsgs()<<", max= "<<stats.iMaxNumMsgs<<", handlers="<<(*it)->getUsageCount()<<((*it)->getRemovePendingState()?" remove pending":"")<<", id="<<(*it)->getQueueDataId()<<std::endl;

			os<<"   Puts:  "<<stats.tsrPut<<std::endl;
			os<<"   Gets:  "<<stats.tsrGet<<std::endl;
			os<<"   Waits: "<<stats.tsrMutexWait<<std::endl;
		}
	}

	{
		for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Temporary);
					it != getQueueTable()->end(); it++) {

			Shared::Queue::Stats stats;
			(*it)->getStats(stats);

			os<<"Q: "<<(*it)->getName()<<", num_msgs = "<<(*it)->getNumMsgs()<<", max= "<<stats.iMaxNumMsgs<<", handlers="<<(*it)->getUsageCount()<<((*it)->getRemovePendingState()?" remove pending":"")<<", id="<<(*it)->getQueueDataId()<<std::endl;

			os<<"   Puts:  "<<stats.tsrPut<<std::endl;
			os<<"   Gets:  "<<stats.tsrGet<<std::endl;
			os<<"   Waits: "<<stats.tsrMutexWait<<std::endl;
		}
	}

	os<<"Active sessions: "<<getSessionTable()->getNumActiveSessions()<<std::endl;

	os<<"Content storage:"<<std::endl;
	getShared()->pContentStorage->dump(os);
	os<<"End of report."<<std::endl;
}
/*************************************************************************/
static stats::Ext::SamplePtr TSR2Sample(const TimeSamplesResults& tsr){

	stats::Ext::SamplePtr dmSample(stats::DataFactory::GetInstance()->createSample());

	dmSample->setMin(tsr.iMin/1000 + tsr.iNumSamples ? 1 : 0);
	dmSample->setMax(tsr.iMax/1000 + tsr.iNumSamples ? 1 : 0);
	dmSample->setAvg(tsr.iNumSamples ? tsr.iTotal/1000 / tsr.iNumSamples + 1: 0);
	dmSample->setTotal(tsr.iTotal/1000 + tsr.iNumSamples ? 1 : 0);
	dmSample->setNum(tsr.iNumSamples);

	return dmSample;
}
/*************************************************************************/
stats::Ext::SystemStatsPtr Attachment::getStats(bool bReset){
	IAS_TRACER;

	stats::Ext::SystemStatsPtr dmAttachment(stats::DataFactory::GetInstance()->createSystemStats());

	dmAttachment->setName(getShared()->sName);

  dmAttachment->createMemory();

  dmAttachment->getMemory()->setSystemHeap(TheMMSystemHeap->getStatistics());
  dmAttachment->getMemory()->setQueueData(TheMMQueueData->getStatistics());
  dmAttachment->getMemory()->setApplicationData(TheMMApplicationData->getStatistics());

	for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Topic);
			it != getQueueTable()->end(); it++) {

		Shared::Queue::Stats stats;
		(*it)->getStats(stats,bReset);

		stats::TopicStats* pTopic=dmAttachment->createTopics();

		pTopic->setName((*it)->getName());
		pTopic->setNumMsgs((*it)->getNumMsgs());
		pTopic->setSize((*it)->getSize());
		pTopic->setHighWater(stats.iMaxNumMsgs);
		pTopic->setHanders((*it)->getUsageCount());
		pTopic->setPuts(TSR2Sample(stats.tsrPut));
		pTopic->setGets(TSR2Sample(stats.tsrGet));
		pTopic->setWaits(TSR2Sample(stats.tsrMutexWait));

		::IAS::DM::Default::Ext::StringList& lstSubscriptions(pTopic->getSubscriptionsList());

		for(Shared::Queue* pCursor=(*it)->getSubscriptionList();
				(*it) != pCursor;
				pCursor = pCursor->getSubscriptionList())
					lstSubscriptions.add(pCursor->getName());

	}

	{
			for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Queue);
						it != getQueueTable()->end(); it++) {

				Shared::Queue::Stats stats;
				(*it)->getStats(stats,bReset);

				stats::QueueStats* pQueue=dmAttachment->createQueues();

				pQueue->setName((*it)->getName());
				pQueue->setNumMsgs((*it)->getNumMsgs());
				pQueue->setSize((*it)->getSize());
				pQueue->setHighWater(stats.iMaxNumMsgs);
				pQueue->setHanders((*it)->getUsageCount());
				pQueue->setPuts(TSR2Sample(stats.tsrPut));
				pQueue->setGets(TSR2Sample(stats.tsrGet));
				pQueue->setWaits(TSR2Sample(stats.tsrMutexWait));

			}
	}

	{
		for(Shared::QueueTable::Iterator it = getQueueTable()->begin(Shared::Queue::QM_Temporary);
					it != getQueueTable()->end(); it++) {

			Shared::Queue::Stats stats;
			(*it)->getStats(stats);

			stats::QueueStats* pQueue=dmAttachment->createQueues();

			pQueue->setName((*it)->getName());
			pQueue->setNumMsgs((*it)->getNumMsgs());
			pQueue->setSize((*it)->getSize());
			pQueue->setHighWater(stats.iMaxNumMsgs);
			pQueue->setHanders((*it)->getUsageCount());
			pQueue->setPuts(TSR2Sample(stats.tsrPut));
			pQueue->setGets(TSR2Sample(stats.tsrGet));
			pQueue->setWaits(TSR2Sample(stats.tsrMutexWait));

		}
	}

	dmAttachment->setGeneratedOn(DateTime(true));

	//TODO (L) content storage stats
	//os<<"Content storage:"<<std::endl;
	//getShared()->pContentStorage->dump(os);
	//os<<"End of report."<<std::endl;

	return dmAttachment;
}
/*************************************************************************/
ContentManager*  Attachment::getContentManager(){
	IAS_TRACER;

	//Mutex::Locker locker() ??

	if(!ptrContentManager)
		IAS_THROW(InternalException("No content created"));

	return ptrContentManager;
}
/*************************************************************************/
Admin::ActionDispatcher* Attachment::getActionDispatcher(){
	IAS_TRACER;
	return ptrActionDispatcher;
}
/*************************************************************************/
Attachment::~Attachment() throw () {
	IAS_TRACER;
	TheMMSystemHeap.pass();
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"** Attachment instance destroyed.");
	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"**");
}
/*************************************************************************/
}
}
}

