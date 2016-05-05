/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/Subscriber.h
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
#ifndef _IAS_QS_FCGI_Subscriber_H_
#define _IAS_QS_FCGI_Subscriber_H_

#include "Receiver.h"

#include <qs/api/Subscriber.h>

namespace IAS {
namespace QS {
namespace FCGI {

/*************************************************************************/
/** The Subscriber class.
 *
 */
class Subscriber :
		public Receiver,
		public virtual API::Subscriber{
public:

	virtual ~Subscriber() throw();


protected:
	Subscriber(Session* pSession, const API::Destination& refDestination);

	friend class Factory<Subscriber>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_FCGI_Subscriber_H_ */
