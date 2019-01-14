/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/Connection.h
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
#ifndef _IAS_DS_ODBC_Connection_H_
#define _IAS_DS_ODBC_Connection_H_

#include <commonlib/commonlib.h>
#include <ds/api/Connection.h>
#include <ds/Impl/Connection.h>
#include <org/invenireaude/qsystem/workers/ds/Parameter.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

class System;

/*************************************************************************/
/** The Connection class.
 *
 */
class Connection : public virtual DS::Impl::Connection {
public:

	virtual ~Connection() throw();

	virtual API::Session* createSession(API::Session::TransactionMode iMode);

	ODBC::System *getSystem();

protected:

	Connection(ODBC::System* pSystem,const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	friend class Factory<Connection>;

	ODBC::System *pSystem;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DS_ODBC_Connection_H_ */
