/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Session.h
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
#ifndef _IAS_QS_Net_Async_Session_H_
#define _IAS_QS_Net_Async_Session_H_

#include <commonlib/commonlib.h>

#include <qs/Impl/net/Session.h>

#include "Conversation.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public Net::Session {
public:

	virtual ~Session() throw();

	virtual API::Producer*   createProducer(const API::Destination& refDestination);
	virtual API::Consumer*   createConsumer(const API::Destination& refDestination);

	virtual API::Requester*  createRequester(const API::Destination& outDestination,
											 const API::Destination& inDestination);

	virtual API::Responder*  createResponder();

	virtual void commit();
	virtual void rollback();

	virtual TransactionMode getMode()const {
		return IAS::QS::API::Session::SM_NonTransacted;
	};

	Engine *getEngine()const;

	Connection *getConnection()const;

protected:
	Session(Connection *pConnection);

	Connection *pConnection;
	Engine   *pEngine;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Net_Async_Session_H_ */
