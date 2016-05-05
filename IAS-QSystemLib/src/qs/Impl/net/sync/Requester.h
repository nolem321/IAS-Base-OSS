/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Requester.h
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
#ifndef _IAS_QS_Net_Sync_Requester_H_
#define _IAS_QS_Net_Sync_Requester_H_

#include <qs/api.h>

#include "Requester.h"
#include "Receiver.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
/** The Requester class.
 *
 */
class Requester : public Receiver,
			      public virtual API::Requester{

public:

	virtual ~Requester() throw();

	virtual bool request(API::Message* pMessage);

protected:
	Requester(Session* pSession,
			const API::Destination& outDestination,
			const API::Destination& inDestination);


	API::Destination outDestination;

	friend class Factory<Requester>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_QS_System_Requester_H_ */

