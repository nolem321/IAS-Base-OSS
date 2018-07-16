/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/Session.h
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
#ifndef _IAS_DS_PostgreSQL_Session_H_
#define _IAS_DS_PostgreSQL_Session_H_

#include <ds/api/Session.h>
#include <qs/fmt/Formatter.h>
#include "libpq-fe.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public virtual API::Session {
public:

	virtual ~Session() throw();


	virtual API::StatementInsert*   createInsert();
	virtual API::StatementCall*     createCall();
	virtual API::StatementSelect*   createSelect();
	virtual API::StatementDelete*   createDelete();
	virtual API::StatementUpdate*   createUpdate();

	Connection* getConnection()const;

	inline PGconn      *getConnectionHandle(){ return conn; }

	QS::Fmt::Formatter* getFormatter()const{
		return pFormatter;
	}

	virtual void beginTxnIfNeed();

protected:
	Session(Connection* pConnection);

	PGconn     *conn;

	Connection* pConnection;

	QS::Fmt::Formatter* pFormatter;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_PostgreSQL_Session_H_ */
