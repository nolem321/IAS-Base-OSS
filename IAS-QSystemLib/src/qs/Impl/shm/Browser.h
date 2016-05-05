/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Browser.h
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
#ifndef _IAS_QS_System_Browser_H_
#define _IAS_QS_System_Browser_H_

#include <qs/api/Browser.h>
#include "Receiver.h"
namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
/** The Browser class.
 *
 */
class Browser :
		public Receiver,
		public virtual API::Browser {
public:

	virtual ~Browser() throw();

	virtual API::Message* receive(int iTimeWait, API::Attributes* pSelector);
	virtual unsigned int skip(unsigned int iOffset);

protected:
	Browser(Session* pSession, const API::Destination& refDestination);

	Shared::Queue::BrowseLocator iLocator;

	friend class Factory<Browser>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Browser_H_ */
