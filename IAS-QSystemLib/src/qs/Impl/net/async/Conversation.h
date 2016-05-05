/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Conversation.h
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
#ifndef _IAS_QS_Net_Async_Conversation_H_
#define _IAS_QS_Net_Async_Conversation_H_

#include <commonlib/commonlib.h>
#include <qs/Impl/net/pump/MsgPumpFactory.h>

namespace IAS {
namespace QS {
namespace Net {

class Message;
namespace Async {

class Engine;

/*************************************************************************/
/** The Conversation class.
 *
 */
class Conversation : public IAS::Net::EventHandler {
public:

	virtual ~Conversation() throw();


	Message* getMessage();

	void putMessage(Message* pMessage);

	typedef long Key;

	const Key& getKey()const{
		return key;
	};

	const static Key C_AnyKey;

	Engine *getEngine()const;
	void    resume();

protected:
	Conversation(IAS::Net::FileHandle* pFileHandle,
				 Engine *pEngine,
				 bool bSuppressInitialization=false);

	Engine *pEngine;

	void initialize(IAS::Net::IBlockIO *pBlockIO);

	virtual void onInputReady();
	virtual void onOutputReady();

	IAS_DFT_FACTORY<Message>::PtrHolder ptrInputMessage;
	IAS_DFT_FACTORY<Message>::PtrHolder ptrOutputMessage;

	Pump::MsgPumpFactory::DataPumpPtr  ptrInputMsgPump;
	Pump::MsgPumpFactory::DataPumpPtr  ptrOutputMsgPump;

	IAS_DFT_FACTORY<IAS::Net::FileHandle>::PtrHolder ptrFileHandle;

	IAS::Net::IBlockIO *pBlockIO;

	Mutex mutex;

	void makeReadable();
	void makeWritable();

	void setDeletePending();

	Key key;

	friend class Factory<Conversation>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Net_Async_Conversation_H_ */
