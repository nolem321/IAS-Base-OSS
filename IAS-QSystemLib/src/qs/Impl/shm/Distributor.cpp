/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Distributor.cpp
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
#include "Distributor.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "Attachment.h"

#include "shared/System.h"
#include "shared/MsgEntry.h"
#include "shared/QueueTable.h"
#include "shared/ContentStorage.h"
#include <unistd.h>
namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Distributor::Worker::Worker(Shared::Queue *pTopic):
	Thread(this){
	IAS_TRACER;
	this->pTopic=pTopic->open();
}
/*************************************************************************/
Distributor::Worker::~Worker(){
	IAS_TRACER;
	if(pTopic)
		pTopic->close();
}
/*************************************************************************/
void Distributor::Worker::run(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Started:"<<(void*)this<<pTopic->getName());

	bool bStop=false;

	while(!bStop && !SYS::Signal::GetInstance()->isStopping()) {


		try{

			//TODO (M) parameter and nice exception handling.
			pTopic->getAndPublish(1000);

		}catch(Exception& e){
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Stopped: "<<(void*)this
						<<" sig="<<SYS::Signal::GetInstance()->isStopping()<<"\n"<<e.toString());
				//TODO (M) recognize exceptions
				bStop=true;;
		}catch(...){
			IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Stopped: "<<(void*)this
					<<" sig="<<SYS::Signal::GetInstance()->isStopping());
			//TODO (M) recognize exceptions
			bStop=true;;
		}
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Stopped:"<<(void*)this<<pTopic->getName());

}
/*************************************************************************/
Distributor::Distributor(Attachment *pAttachment):pAttachment(pAttachment),
	iLastVersion(0){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pAttachment);
}
/*************************************************************************/
void Distributor::updateWorkers(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Updating workers !");

	long iNextVersion = pAttachment->getQueueTable()->getTopicInfoVersion();

	if(iNextVersion == iLastVersion)
		return;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Updating workers:"<<iNextVersion-iLastVersion);

	Shared::QueueTable::Iterator it = pAttachment->getQueueTable()->begin(Shared::Queue::QM_Topic);

	while(it != pAttachment->getQueueTable()->end()){

		if(hmWorkers.count(*it) == 0){

			try{
				IAS_DFT_FACTORY<Worker>::PtrHolder ptrNewWorker(IAS_DFT_FACTORY<Worker>::Create(*it));
				ptrNewWorker->start();
				hmWorkers[*it]=ptrNewWorker.pass();
			}catch(Exception& e){
				IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Failed:"<<e.toString());
			}

		}

		it++;
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Updating workers:"<<hmWorkers.size());

	iLastVersion=iNextVersion;
}
/*************************************************************************/
void Distributor::start(){
	IAS_TRACER;

	//TODO some locks on updates ? o co chodzi ?


	while(!SYS::Signal::GetInstance()->isStopping()){
		updateWorkers();
		sleep(10);
	}

	WorkersMap::iterator it=hmWorkers.begin();

	while(it!=hmWorkers.end()){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Stopping, and waiting for:"<<(it->second->pTopic->getName()));
		//TODO timed waits and cancels.
		(it->second)->join();
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Stopped:"<<(it->second->pTopic->getName()));
		it++;
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Finished.");
}
/*************************************************************************/
void Distributor::dumpInfo(std::ostream& os){
	IAS_TRACER;
	//os<<"Distributor: ["<<pSystem->getShared()->sName<<"]"<<std::endl;
}
/*************************************************************************/
Distributor::~Distributor() throw () {
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
