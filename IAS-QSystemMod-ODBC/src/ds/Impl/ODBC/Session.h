/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/Session.h
 *
 * Licensed under the Invenire Aude Commercial License (the "License");
 * you may not use this file except in compliance with the License.
 * You may find the license terms and conditions in the LICENSE.txt file.
 * or at http://www.invenireaude.com/licenses/license.txt
 *
 * This file and any derived form, including but not limited to object
 * executable, represents the Confidential Materials.
 *
 */
#ifndef _IAS_DS_ODBC_Session_H_
#define _IAS_DS_ODBC_Session_H_

#include <ds/api/Session.h>

#include <qs/fmt/FmtFactory.h>
#include <ds/Impl/Session.h>

#include "tools/Handle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

class Connection;

/*************************************************************************/
/** The Session class.
 *
 */
class Session : public  DS::Impl::Session {
public:

	virtual ~Session() throw();


	virtual API::StatementInsert*   createInsert();
	virtual API::StatementCall*     createCall();
  virtual API::StatementFunCall*  createFunCall();
	virtual API::StatementSelect*   createSelect();
	virtual API::StatementDelete*   createDelete();
	virtual API::StatementUpdate*   createUpdate();

	Connection* getConnection()const;

	inline Tools::HandleDBC::handle_type getDBCHandle(){ return handleDBC.get(); }

protected:
	Session(Connection* pConnection, SQLSMALLINT iAutoCommit);

	Tools::HandleDBC handleDBC;

	Connection* pConnection;

	friend class Factory<Session>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_ODBC_Session_H_ */
