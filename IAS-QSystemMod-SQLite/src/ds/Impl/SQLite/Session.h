/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/Session.h
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
#ifndef _IAS_DS_SQLite_Session_H_
#define _IAS_DS_SQLite_Session_H_

#include <ds/api/Session.h>
#include <qs/fmt/Formatter.h>
#include <ds/Impl/Session.h>
#include <sqlite3.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public DS::Impl::Session {
public:

	virtual ~Session() throw();


	virtual API::StatementInsert*   createInsert();
	virtual API::StatementCall*     createCall();
	virtual API::StatementSelect*   createSelect();
	virtual API::StatementDelete*   createDelete();
	virtual API::StatementUpdate*   createUpdate();

	Connection* getConnection()const;

	inline sqlite3 *getDBHandle(){ return db; }

	virtual void beginTxnIfNeed();

protected:
	Session(Connection* pConnection);

	sqlite3 *db;

	Connection* pConnection;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_SQLite_Session_H_ */
