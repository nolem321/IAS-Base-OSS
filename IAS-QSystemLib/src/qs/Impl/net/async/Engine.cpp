/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Engine.cpp
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
#include <qs/log/LogLevel.h>


#include "Engine.h"
#include "Conversation.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {

/*************************************************************************/
class ConversationFactory : public IAS::Net::Socket::ServiceHandleFactory{
public:

	virtual ~ConversationFactory() throw(){};

	void createService(::IAS::Net::FileHandle* pFileHandle){
		IAS_TRACER;
		pEngine->insert(IAS_DFT_FACTORY<Conversation>::Create(pFileHandle,pEngine));
	}

	ConversationFactory(Engine *pEngine):
		pEngine(pEngine){};

	Engine*                 pEngine;
};
/*************************************************************************/
Engine::Engine(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
		       System *pSystem,
			   bool bSuppressInitialization):
	IAS::Net::Server(IAS::Net::Peer(dmConnection->getHost(),dmConnection->isSetPort() ? dmConnection->getPort() : 50000)),
	pSystem(pSystem){
	IAS_TRACER;

	ptrEventMonitor = IAS::Net::EventMonitor::Create();

	if(!bSuppressInitialization)
		ptrEventMonitor->addHandler(IAS_DFT_FACTORY<IAS::Net::Socket::EventHandler>::Create(
				IAS_DFT_FACTORY<ConversationFactory>::Create(this),this));
}
/*************************************************************************/
Engine::~Engine() throw(){
	IAS_TRACER;
}
/*************************************************************************/
Conversation *Engine::getAvailableForReading(const Conversation::Key& key){
	IAS_TRACER;
	return getAvailableConversation(setReadableConversations,key);
}
/*************************************************************************/
Conversation *Engine::getAvailableForWriting(const Conversation::Key& key){
	IAS_TRACER;
	return getAvailableConversation(setWritableConversations,key);
}
/*************************************************************************/
Conversation *Engine::getAvailableConversation(ConversationsSet& setAvailableConversations,
											   const Conversation::Key& key){
	IAS_TRACER;

	Thread::Cancellation ca(false);

	Conversation *pConversation;

	while(!checkAvailableConversations(setAvailableConversations,pConversation,key)){

		Thread::Cancellation::Test();
		IAS::Net::EventMonitor::ServiceTask service(ptrEventMonitor);
		service.work();
	}

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Get conversation: "<<pConversation->getKey());

	return pConversation;
}
/*************************************************************************/
bool Engine::checkAvailableConversations(ConversationsSet& setAvailableConversations,
										 Conversation* &refPtrConversation,
										 const Conversation::Key& key){
	IAS_TRACER;

	Mutex::Locker locker(mutex);

	ConversationsSet::iterator itResult;

	if(key != Conversation::C_AnyKey){
		ConversationsMap::iterator it = hmConversationByKey.find(key);

		if(it == hmConversationByKey.end())
			IAS_THROW(ItemNotFoundException()<<"Conversation key: "<<key);

		itResult=setAvailableConversations.find(it->second);
	}else{
		itResult=setAvailableConversations.begin();
	}

	if(itResult == setAvailableConversations.end())
		return false;

	refPtrConversation = *itResult;
	setAvailableConversations.erase(itResult);

	return true;
}
/*************************************************************************/
void Engine::insert(Conversation* pConversation){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Insert: "<<pConversation->getKey());

	if(hmConversationByKey.count(pConversation->getKey()))
		IAS_THROW(InternalException("Conversation key already exists: ")<<pConversation->getKey());

	hmConversationByKey[pConversation->getKey()]=pConversation;
	ptrEventMonitor->addHandler(pConversation);
}
/*************************************************************************/
void Engine::addWritable(Conversation* pConversation){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Available WR: "<<pConversation->getKey());
	setWritableConversations.insert(pConversation);
}
/*************************************************************************/
void Engine::addReadable(Conversation* pConversation){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Available RD: "<<pConversation->getKey());
	setReadableConversations.insert(pConversation);
}
/*************************************************************************/
int Engine::remove(Conversation* pConversation){
	IAS_TRACER;
	Mutex::Locker locker(mutex);
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"Remove: "<<pConversation->getKey());

	int iResult=0;

	if(setWritableConversations.count(pConversation)){
		setWritableConversations.erase(pConversation);
		iResult++;
	}

	if(setReadableConversations.count(pConversation)){
		setReadableConversations.erase(pConversation);
		iResult++;
	}

	hmConversationByKey.erase(pConversation->getKey());

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"iResult: "<<iResult);

	return iResult;
}
/*************************************************************************/
void Engine::resumeConversation(Conversation* pConversation){
	IAS_TRACER;
	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"resume: "<<pConversation->getKey());
	ptrEventMonitor->afterService(pConversation);
}
/*************************************************************************/
IAS::Net::EventMonitor*  Engine::getEventMonitor()const{
	IAS_TRACER;
	return ptrEventMonitor;
}
/*************************************************************************/
System*  Engine::getSystem()const{
	IAS_TRACER;
	return pSystem;
}
/*************************************************************************/
}
}
}
}
