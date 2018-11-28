/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementCall.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_StatementCall_H_
#define _IAS_DS_Impl_PostgreSQL_StatementCall_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementCall.h>

#include "Statement.h"
#include "Output.h"
#include "Input.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
/** The StatementCall class.
 *
 */
class StatementCall :
		public virtual Statement,
		public virtual API::StatementCall,
		public virtual Output{
public:

	virtual ~StatementCall() throw();
	virtual void execute();

protected:
	StatementCall(Session* pSession);

	friend class Factory<StatementCall>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_StatementCall_H_ */
