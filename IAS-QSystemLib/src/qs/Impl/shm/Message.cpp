/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Message.cpp
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
#include "Message.h"
#include<qs/log/LogLevel.h>
#include "ContentManager.h"
#include <qs/Impl/base/Attributes.h>

#include <commonlib/commonlib.h>
#include <qs/Impl/shm/shared/MsgEntry.h>
#include <unistd.h>

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Message::Message(const SHM::Shared::MsgEntry& entry):
	entry(entry){
	IAS_TRACER;

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isInfo(),"*** New Message: ");

	ptrContent=IAS_DFT_FACTORY<Content>::Create< const SHM::Shared::ContentStorage::Descriptor& >(entry.getData());
	ptrAttributes=IAS_DFT_FACTORY<QS::Base::Attributes>::Create();

	IAS_DFT_FACTORY<Content>::PtrHolder ptrAttrContent(
			IAS_DFT_FACTORY<Content>::Create< const SHM::Shared::ContentStorage::Descriptor& >(entry.getAttributes()));

	ptrAttributes->read(*ptrAttrContent);

	if(! ptrAttributes->isSet(API::Attributes::CA_MID)){
		static Mutex _mutexIDGen;
		static long  i;
		Mutex::Locker locker(_mutexIDGen);
		//TODO (L)  beter id generator.
		ptrAttributes->setMID("MID"+TypeTools::IntToString((long)time(0)+getpid()+i++,12));
	}

	IAS_LOG(IAS::QS::LogLevel::INSTANCE.isDetailedInfo(),"lepszy generator id!: "<<ptrAttributes->getMID());

}
/*************************************************************************/
Message::~Message() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Content* Message::getContent(){
	IAS_TRACER;
	return ptrContent;
}
/*************************************************************************/
const Shared::MsgEntry& Message::getEntry(){
	IAS_TRACER;

	IAS_DFT_FACTORY<Content>::PtrHolder ptrAttrContent(
			IAS_DFT_FACTORY<Content>::Create< const SHM::Shared::ContentStorage::Descriptor& >(entry.getAttributes()));

	ptrAttributes->write(*ptrAttrContent);
	return entry;
}
/*************************************************************************/
API::Attributes* Message::getAttributes(){
	IAS_TRACER;
	return ptrAttributes;
}
/*************************************************************************/

}
}
}
