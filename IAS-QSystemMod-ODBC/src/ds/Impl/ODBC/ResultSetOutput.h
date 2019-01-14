/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/ResultSetOutput.h 
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
#ifndef _IAS_DS_Impl_ODBC_ResultSetOutput_H_
#define _IAS_DS_Impl_ODBC_ResultSetOutput_H_

#include <commonlib/commonlib.h>
#include <ds/api/IResultSetOutput.h>

#include "Statement.h"
#include "holder/Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
class Session;
/*************************************************************************/
/** The ResultSetOutput class.
 *
 */
class ResultSetOutput :
		public virtual DS::API::IResultSetOutput {
public:

	virtual ~ResultSetOutput() throw();

	virtual void addResultSetOutput(DM::Tools::Setter* pSetter, bool bOptional);
	virtual void bindResultSetOutputs();

	virtual bool next();
	virtual void fetch(int iIdx, DM::DataObjectPtr& dm);

	virtual void close();

protected:
	ResultSetOutput(Statement& statement);

	Holder::Base::Table			   			     tabHolders;

	Statement& statement;

	void fetchImpl(DM::DataObjectPtr& dm);

	bool bHasData;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_ODBC_ResultSetOutput_H_ */
