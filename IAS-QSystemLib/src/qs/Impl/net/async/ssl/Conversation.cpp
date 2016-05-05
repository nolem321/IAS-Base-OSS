/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/ssl/Conversation.cpp
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
#include "Conversation.h"

#include <qs/Impl/net/Message.h>

#include "../Engine.h"
#include "Engine.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
namespace SSL {

/*************************************************************************/
Conversation::Conversation(IAS::Net::FileHandle* pFileHandle,
							Engine *pEngine):
	Async::Conversation(pFileHandle,pEngine,true),
	bAccepted(false){

	IAS_TRACER;

	ptrBIO=IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::Create(pFileHandle);
	ptrSecureLayer=IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerServer>::Create(pEngine->getContext(),ptrBIO);

	subscribe(ET_OutputReady);
	subscribe(ET_InputReady);

	accept();
}
/*************************************************************************/
Conversation::~Conversation() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Conversation::accept(){

	IAS_TRACER;

	if(!ptrSecureLayer->accept()){
		bAccepted=true;
		unsubscribe(ET_OutputReady);
		unsubscribe(ET_InputReady);
		initialize(ptrSecureLayer);
	}
}
/*************************************************************************/
void Conversation::onInputReady(){
	IAS_TRACER;

	if(!bAccepted)
		accept();
	else
		Async::Conversation::onInputReady();
}
/*************************************************************************/
void Conversation::onOutputReady(){
	IAS_TRACER;

	if(!bAccepted)
		accept();
	else
		Async::Conversation::onOutputReady();
}
/*************************************************************************/
IAS::Net::IBlockIO *Conversation::getBlockIO(){
	IAS_TRACER
	return ptrSecureLayer;
}
/*************************************************************************/
}
}
}
}
}
