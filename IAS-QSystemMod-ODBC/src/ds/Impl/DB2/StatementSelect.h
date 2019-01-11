/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/StatementSelect.h 
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
#ifndef _IAS_DS_Impl_DB2_StatementSelect_H_
#define _IAS_DS_Impl_DB2_StatementSelect_H_

#include <commonlib/commonlib.h>

#include <ds/api/StatementSelect.h>

#include "Statement.h"
#include "Input.h"
#include "ResultSetOutput.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
/** The StatementSelect class.
 *
 */
class StatementSelect :
		public virtual Statement,
		public virtual API::StatementSelect,
		public virtual Input,
		public virtual ResultSetOutput{
public:

	virtual ~StatementSelect() throw();

protected:
	StatementSelect(Session* pSession);

	friend class Factory<StatementSelect>;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_DB2_StatementSelect_H_ */
