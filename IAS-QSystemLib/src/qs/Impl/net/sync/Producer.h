/*
 * File: IAS-QSystemLib/src/qs/Impl/net/sync/Producer.h
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
#ifndef _IAS_QS_Net_Sync_Producer_H_
#define _IAS_QS_Net_Sync_Producer_H_

#include <qs/api/Producer.h>

#include "Sender.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Sync{

/*************************************************************************/
/** The Producer class.
 *
 */
class Producer :
		    public Sender,
			public virtual API::Producer{
public:

	virtual ~Producer() throw();

protected:
	Producer(Session* pSession, const API::Destination& refDestination);

	friend class Factory<Producer>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_QS_Net_Sync_Producer_H_ */
