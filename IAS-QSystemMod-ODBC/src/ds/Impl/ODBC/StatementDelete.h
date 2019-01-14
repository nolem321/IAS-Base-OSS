/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/StatementDelete.h 
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
#ifndef _IAS_DS_Impl_ODBC_StatementDelete_H_
#define _IAS_DS_Impl_ODBC_StatementDelete_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementDelete.h>

#include "Statement.h"
#include "Input.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
/** The StatementDelete class.
 *
 */
class StatementDelete :
		public virtual Statement,
		public virtual API::StatementDelete,
		public virtual Input{
public:

	virtual ~StatementDelete() throw();

protected:
	StatementDelete(Session* pSession);

	friend class Factory<StatementDelete>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_ODBC_StatementDelete_H_ */
