/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/SharedBrowserWorker.cpp
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
#include "SharedBrowserWorker.h"
#include<qs/log/LogLevel.h>
#include <commonlib/commonlib.h>

#include <org/invenireaude/qsystem/workers/Attribute.h>
#include <org/invenireaude/qsystem/workers/io/DataFactory.h>

#include <org/invenireaude/qsystem/workers/Connection.h>
#include <org/invenireaude/qsystem/workers/io/Input.h>
#include <org/invenireaude/qsystem/workers/DataFactory.h>

#include <qs/workers/proc/wcm/WorkContextManager.h>

using namespace ::org::invenireaude::qsystem::workers;

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
SharedBrowserWorker::SharedBrowserWorker(const ::org::invenireaude::qsystem::workers::io::SharedBrowserInput* dmParameters):
        Thread(this),
        bEndOfData(false),
        iTimeout(0),
        bAutoRecycle(false),
        iNumReaders(0){
	IAS_TRACER;

	this->dmParameters=dmParameters;

	if(!this->dmParameters->isSetTxnMode() ||
	   this->dmParameters->getTxnMode().compare("NONTXN") != 0)
		IAS_THROW(BadUsageException("The transaction mode must be set to NONTXN for SharedBrowserInput"));

	if(this->dmParameters->isSetTimeout())
		iTimeout=dmParameters->getTimeout();

	if(this->dmParameters->isSetAutoRecycle())
		bAutoRecycle=dmParameters->getAutoRecycle();

}
/*************************************************************************/
SharedBrowserWorker::~SharedBrowserWorker() throw(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Deleted: "<<(void*)this);
}
/*************************************************************************/
void SharedBrowserWorker::enqueueNextMessage(API::Browser* pBrowser){
	IAS_TRACER;

	API::Message::PtrHolder ptrMessage;

	ptrMessage=pBrowser->receive(iTimeout);

	Mutex::Locker locker(mutex);

	while(phcMessages.size() >= iMaxMessagesInQueue){
		Thread::Cancellation tc(true);
		mutex.wait(cndWriters);
	}

	phcMessages.addPointer(ptrMessage.pass());

	cndReaders.signal();

}
/*************************************************************************/
API::Message *SharedBrowserWorker::getNextMessage(int iTimeout){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	while(phcMessages.size() == 0){

		if(bEndOfData){
			IAS_THROW(EndOfDataException(dmParameters->getDestination()));
		}

		Thread::Cancellation tc(true);
		mutex.wait(cndReaders,iTimeout);
	}

	API::Message *pMessage = *phcMessages.begin();

	phcMessages.forget(pMessage);

	cndWriters.signal();

	return pMessage;
}
/*************************************************************************/
void SharedBrowserWorker::run(){
	IAS_TRACER;

	Thread::Cancellation tc(false);
	WCM::IO::Context io;

	EOWBroadcaster broadcaster(*this);

	API::Browser::PtrHolder            ptrBrowser;

	URI key;

	API::Connection *pConnection=io.lookupConnection(key,dmParameters->getConnection());

	API::Session* pSession=io.lookupSession(key,dmParameters);
	ptrBrowser=pSession->createBrowser(dmParameters->getDestination());

	try{

		while(!SYS::Signal::GetInstance()->isStopping())
			try{

				enqueueNextMessage(ptrBrowser);

			}catch(EndOfDataException& e){

				if(!bAutoRecycle)
					throw;

				ptrBrowser=pSession->createBrowser(dmParameters->getDestination());
				enqueueNextMessage(ptrBrowser);
			}

	}catch (EndOfDataException& e) {
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Thread ended with exception: "<<e.toString());
	}catch(Exception& e){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Thread ended with exception: "<<e.toString());
#ifdef __GNUC__
	}catch(__cxxabiv1::__forced_unwind&){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"__forced_unwind exception");
		throw;
#endif
	}catch(...){
		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isError(),"Unknown exception");
	}

}
/*************************************************************************/
void SharedBrowserWorker::broadcastEndOfWork(){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	bEndOfData=true;
	cndReaders.broadcast();

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Finish");
}
/*************************************************************************/
void SharedBrowserWorker::addReader(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	iNumReaders++;
}
/*************************************************************************/
bool SharedBrowserWorker::removeReader(){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	return --iNumReaders == 0;
}
/*************************************************************************/
}
}
}
}
}
