/*
 * File: IAS-QSystemLib/src/qs/Impl/sdf/SessionAutoCommit.h
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
#ifndef _IAS_QS_SDF_SessionAutoCommit_H_
#define _IAS_QS_SDF_SessionAutoCommit_H_

#include "Session.h"

namespace IAS {
namespace QS {
namespace SDF {

class Connection;

/*************************************************************************/
/** The SessionAutoCommit class.
 *
 */
class SessionAutoCommit :
		public virtual Session{
public:

	virtual ~SessionAutoCommit() throw();

	virtual void commit();
	virtual void rollback();

	virtual TransactionMode getMode()const;

protected:
	SessionAutoCommit(Connection* pConnection);

	friend class Factory<SessionAutoCommit>;
};

/*************************************************************************/
}
}
}

#endif /* _IAS_QS_SDF_SessionAutoCommit_H_ */
