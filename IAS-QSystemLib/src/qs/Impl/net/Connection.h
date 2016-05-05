/*
 * File: IAS-QSystemLib/src/qs/Impl/net/Connection.h
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
#ifndef _IAS_QS_Net_Connection_H_
#define _IAS_QS_Net_Connection_H_

#include <commonlib/commonlib.h>
#include <qs/api/Connection.h>

namespace IAS {
namespace QS {
namespace Net {

class System;
class BlockIOWrapperFactory;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual API::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Message*         createMessage();
	virtual API::ContentManager*  getContentManager();

	const Net::System *getSystem();

	virtual API::Administrator*   createAdministrator();

protected:
	Connection(const Net::System* pSystem);

	const Net::System *pSystem;

	friend class Factory<Connection>;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_QS_Net_Connection_H_ */
