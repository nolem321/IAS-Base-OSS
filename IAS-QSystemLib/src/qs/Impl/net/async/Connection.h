/*
 * File: IAS-QSystemLib/src/qs/Impl/net/async/Connection.h
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
#ifndef _IAS_QS_Net_Async_Connection_H_
#define _IAS_QS_Net_Async_Connection_H_

#include <commonlib/commonlib.h>

#include "../Connection.h"

namespace IAS {
namespace QS {
namespace Net {
namespace Async {

class System;
class Engine;
/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public QS::Net::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession(API::Session::TransactionMode iMode);

	Engine* getEngine()const{
		return pEngine;
	}

protected:
	Connection(const System* pSystem, Engine* pEngine);

	Engine* pEngine;

	friend class Factory<Connection>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_QS_Net_Async_Connection_H_ */
