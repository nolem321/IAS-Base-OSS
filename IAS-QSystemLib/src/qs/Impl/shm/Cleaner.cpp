/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Cleaner.cpp
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
#include "Cleaner.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "shared/System.h"
#include "shared/Session.h"
#include "shared/SessionTable.h"

#include "Attachment.h"
#include <unistd.h>
namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Cleaner::Cleaner(Attachment *pAttachment):pAttachment(pAttachment){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pAttachment);
}
/*************************************************************************/
Cleaner::~Cleaner() throw () {
	IAS_TRACER;
}

/*************************************************************************/
void Cleaner::work(){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," == Waking up ==.");

	Shared::SessionTable *pSessionTable = pAttachment->getSessionTable();

	Shared::SessionTable::Iterator it=pSessionTable->begin();
	Shared::SessionTable::Iterator itEnd=pSessionTable->end();

	while(it != itEnd){

		IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo()," Session: ");
		(*it)->tryToClean();
		it++;
	}


	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Sleeping ...");
}
/*************************************************************************/
void Cleaner::start(){
	IAS_TRACER;

	while(!SYS::Signal::GetInstance()->isStopping()){
		work();
		sleep(1);
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"Finished.");
}
/*************************************************************************/
}
}
}
