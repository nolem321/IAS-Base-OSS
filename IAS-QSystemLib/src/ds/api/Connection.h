/*
 * File: IAS-QSystemLib/src/ds/api/Connection.h
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
#ifndef _IAS_DS_API_Connection_H_
#define _IAS_DS_API_Connection_H_

#include "Session.h"

namespace IAS {
namespace DS {
namespace API {

class Session;
class Message;
class ContentManager;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection {
public:

	virtual ~Connection() throw(){};

	virtual Session* createSession(Session::TransactionMode iMode)=0;

	typedef IAS_DFT_FACTORY<Connection>::PtrHolder PtrHolder;
};
/*************************************************************************/
}
}
}

#endif /* _IAS_DS_API_Connection_H_ */
