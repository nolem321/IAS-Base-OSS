/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Engine.h
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
#ifndef _IAS_QS_Net_Async_Engine_H_
#define _IAS_QS_Net_Async_Engine_H_

#include <commonlib/commonlib.h>

#include <qs/api.h>

#include "Conversation.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
class System;
/*************************************************************************/
/** The Engine class.
 *
 */
class Engine : public ::IAS::Net::Server{
public:

	virtual ~Engine() throw();

	Conversation *getAvailableForReading(const Conversation::Key& key=Conversation::C_AnyKey);
	Conversation *getAvailableForWriting(const Conversation::Key& key=Conversation::C_AnyKey);

	void addWritable(Conversation* pConversation);
	void addReadable(Conversation* pConversation);

	void insert(Conversation* pConversation);
	int  remove(Conversation* pConversation);

	void resumeConversation(Conversation* pConversation);

	struct Resume{
		void operator()(Conversation* pConversation){
			pConversation->resume();
		};
	};

	typedef PtrHolder<Conversation,Resume> AutoResume;

	IAS::Net::EventMonitor*  getEventMonitor()const;

	System* getSystem()const;

protected:
	Engine(const ::org::invenireaude::qsystem::workers::Connection* dmConnection,
		   System* pSystem,
		   bool bSuppressInitialization=false);

	IAS::Net::EventMonitor::PtrHolder                  ptrEventMonitor;

	Mutex mutex;

	typedef std::set<Conversation*>                   ConversationsSet;
	typedef std::map<Conversation::Key,Conversation*> ConversationsMap;

	ConversationsSet	   				 setReadableConversations;
	ConversationsSet	   				 setWritableConversations;

	ConversationsMap	   				 hmConversationByKey;

	bool checkAvailableConversations(ConversationsSet& setReadAvailableConversations,
									 Conversation* &refPtrConversation,
									 const Conversation::Key& key);

	Conversation *getAvailableConversation(ConversationsSet& setReadAvailableConversations,
							   	   	   	   const Conversation::Key& key=Conversation::C_AnyKey);

	System *pSystem;

	friend class Factory<Engine>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Net_Async_Engine_H_ */
