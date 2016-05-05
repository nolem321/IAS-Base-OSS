/*
 * File: IAS-QSystemLib/src/qs/api/Session.h
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
#ifndef _IAS_QS_API_Session_H_
#define _IAS_QS_API_Session_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace QS {
namespace API {

class Producer;
class Consumer;
class Browser;
class Subscriber;
class Publisher;
class Destination;

class Requester;
class Responder;
class Controller;

/*************************************************************************/
/** The Session class.
 *
 */
class Session {
public:

	virtual ~Session() throw(){};

	virtual Controller*  createController(const Destination& refDestination)=0;

	virtual Producer*   createProducer(const Destination& refDestination)=0;
	virtual Consumer*   createConsumer(const Destination& refDestination)=0;
	virtual Browser*    createBrowser(const Destination& refDestination)=0;
	virtual Subscriber* createSubscriber(const Destination& refDestination)=0;
	virtual Publisher*  createPublisher(const Destination& refDestination)=0;

	virtual Requester*  createRequester(const API::Destination& outDestination,
			 	 	 	 	 	 	 	 const API::Destination& inDestination)=0;

	virtual Responder*  createResponder()=0;

	enum TransactionMode {
		SM_NonTransacted,
		SM_Transacted,
		SM_XAManaged
	};

	virtual void commit()=0;
	virtual void rollback()=0;

	virtual TransactionMode getMode()const=0;

	typedef IAS_DFT_FACTORY<Session>::PtrHolder PtrHolder;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_API_Session_H_ */
