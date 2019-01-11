/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/SessionXAManaged.h 
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
#ifndef _IAS_DS_Oracle_SessionXAManaged_H_
#define _IAS_DS_Oracle_SessionXAManaged_H_

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

class Connection;

/*************************************************************************/
/** The SessionXAManaged class.
 *
 */
class SessionXAManaged :
		public virtual Session{
public:

	virtual ~SessionXAManaged() throw();

	virtual void commit();
	virtual void rollback();

	virtual TransactionMode getMode()const;

protected:
	SessionXAManaged(Connection* pConnection);

	friend class Factory<SessionXAManaged>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DS_Oracle_SessionXAManaged_H_ */
