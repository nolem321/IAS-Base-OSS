/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/StatementUpdate.h 
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
#ifndef _IAS_DS_Impl_DB2_StatementUpdate_H_
#define _IAS_DS_Impl_DB2_StatementUpdate_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementUpdate.h>

#include "Statement.h"
#include "Input.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
/** The StatementUpdate class.
 *
 */
class StatementUpdate :
		public virtual Statement,
		public virtual API::StatementUpdate,
		public virtual Input{
public:

	virtual ~StatementUpdate() throw();

protected:
	StatementUpdate(Session* pSession);

	friend class Factory<StatementUpdate>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_DB2_StatementUpdate_H_ */
