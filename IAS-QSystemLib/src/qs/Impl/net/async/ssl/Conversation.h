/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/ssl/Conversation.h
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
#ifndef _IAS_QS_Net_Async_SSL_Conversation_H_
#define _IAS_QS_Net_Async_SSL_Conversation_H_

#include <commonlib/commonlib.h>
#include <commonlib/net/ssl/ssl.h>

#include "../Conversation.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {
namespace SSL {
class Engine;
/*************************************************************************/
/** The Conversation class.
 *
 */
class Conversation : public Async::Conversation {
public:

	virtual ~Conversation() throw();

protected:
	Conversation(IAS::Net::FileHandle* pFileHandle,
				 Engine *pEngine);

	virtual IAS::Net::IBlockIO *getBlockIO();

	void accept();

	virtual void onInputReady();
	virtual void onOutputReady();

	IAS_DFT_FACTORY<IAS::Net::SSL::BlockIO>::PtrHolder           ptrBIO;
	IAS_DFT_FACTORY<IAS::Net::SSL::SecureLayerServer>::PtrHolder ptrSecureLayer;

	bool bAccepted;

	friend class Factory<Conversation>;
};
/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_QS_Net_Async_SSL_Conversation_H_ */
