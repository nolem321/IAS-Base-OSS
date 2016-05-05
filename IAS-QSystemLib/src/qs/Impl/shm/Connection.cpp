/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Connection.cpp
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
#include "Connection.h"
#include<qs/log/LogLevel.h>

#include <commonlib/commonlib.h>

#include "SessionAutoCommit.h"
#include "SessionTransacted.h"
#include "Content.h"
#include "Message.h"
#include "ContentManager.h"

#include "Administrator.h"

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
Connection::Connection(SHM::Attachment* pAttachment):
		pAttachment(pAttachment){
	IAS_TRACER;

	IAS_CHECK_IF_NULL(pAttachment);
}
/*************************************************************************/
API::Session* Connection::createSession(API::Session::TransactionMode iMode){
	IAS_TRACER;

	switch(iMode){

		case API::Session::SM_Transacted:
			return IAS_DFT_FACTORY<QS::SHM::SessionTransacted>::Create(this);

		case API::Session::SM_NonTransacted:
			return IAS_DFT_FACTORY<QS::SHM::SessionAutoCommit>::Create(this);

	default:
		IAS_THROW(BadUsageException("Unsupported session mode requested for the SHM module."));
	}
}
/*************************************************************************/
SHM::Attachment *Connection::getAttachment(){
	IAS_TRACER;
	IAS_CHECK_IF_NULL(pAttachment);
	return pAttachment;
}
/*************************************************************************/
API::Message* Connection::createMessage(){
	IAS_TRACER;


	IAS_DFT_FACTORY<Content>::PtrHolder ptrAttrContent(pAttachment->getContentManager()->allocateImpl());
	IAS_DFT_FACTORY<Content>::PtrHolder ptrDataContent(pAttachment->getContentManager()->allocateImpl());

	Shared::MsgEntry entry(ptrAttrContent->getDescriptor(),ptrDataContent->getDescriptor());

	return IAS_DFT_FACTORY< QS::SHM::Message >::Create(entry);
}
/*************************************************************************/
API::ContentManager* Connection::getContentManager(){
	IAS_TRACER;
	return pAttachment->getContentManager();
}
/*************************************************************************/
Connection::~Connection() throw(){
	IAS_TRACER;
}
/*************************************************************************/
API::Administrator*   Connection::createAdministrator(){
	IAS_TRACER;

	return IAS_DFT_FACTORY<QS::SHM::Administrator>::Create(pAttachment);
}
/*************************************************************************/
}
}
}
