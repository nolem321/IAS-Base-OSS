/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/StatementFunCall.h
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
#ifndef _IAS_DS_Impl_PostgreSQL_StatementFunCall_H_
#define _IAS_DS_Impl_PostgreSQL_StatementFunCall_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementFunCall.h>

#include "Statement.h"
#include "Output.h"
#include "Input.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
/** The StatementFunCall class.
 *
 */
class StatementFunCall :
		public virtual Statement,
		public virtual API::StatementFunCall,
		public virtual Output{
public:

	virtual ~StatementFunCall() throw();
	virtual void execute();

	virtual void setSQLText(const String& strSQLText);

protected:
	StatementFunCall(Session* pSession);

	friend class Factory<StatementFunCall>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_PostgreSQL_StatementFunCall_H_ */
