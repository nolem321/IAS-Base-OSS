/*
 * File: IAS-QSystemMod-FCGI/src/qs/Impl/fcgi/Publisher.h
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
#ifndef _IAS_QS_FCGI_Publisher_H_
#define _IAS_QS_FCGI_Publisher_H_

#include <qs/api/Publisher.h>

#include "Sender.h"

namespace IAS {
namespace QS {
namespace FCGI {

/*************************************************************************/
/** The Publisher class.
 *
 */
class Publisher :
		    public Sender,
			public virtual API::Publisher{
public:

	virtual ~Publisher() throw();

protected:
	Publisher(Session* pSession, const API::Destination& refDestination);

	friend class Factory<Publisher>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_FCGI_Publisher_H_ */
