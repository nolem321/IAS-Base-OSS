/*
 * File: IAS-QSystemLib/src/qs/Impl/shm/Connection.h
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
#ifndef _IAS_QS_System_Connection_H_
#define _IAS_QS_System_Connection_H_

#include <commonlib/commonlib.h>
#include <qs/api/Connection.h>
#include <qs/Impl/shm/Attachment.h>

namespace IAS {
namespace QS {
namespace SHM {

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual API::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession(API::Session::TransactionMode iMode);
	virtual API::Administrator*   createAdministrator();

	virtual API::Message*         createMessage();
	virtual API::ContentManager*  getContentManager();

	SHM::Attachment* getAttachment();

protected:
	Connection(SHM::Attachment* pAttachment);

	friend class Factory<Connection>;

	SHM::Attachment *pAttachment;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_System_Connection_H_ */
