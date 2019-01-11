/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/SessionTransacted.h 
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
#ifndef _IAS_DS_DB2_SessionTransacted_H_
#define _IAS_DS_DB2_SessionTransacted_H_

#include "Session.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
/** The SessionTransacted class.
 *
 */
class SessionTransacted : public virtual Session{
public:

	virtual ~SessionTransacted() throw();

	virtual void commit();
	virtual void rollback();

	virtual TransactionMode getMode()const;

protected:
	SessionTransacted(Connection* pConnection);

	friend class Factory<SessionTransacted>;
};

/*************************************************************************/
}
}
}
}
#endif /* _IAS_DS_DB2_SessionTransacted_H_ */
