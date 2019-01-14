/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/Input.h 
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
#ifndef _IAS_DS_Impl_ODBC_Input_H_
#define _IAS_DS_Impl_ODBC_Input_H_

#include <commonlib/commonlib.h>
#include <ds/api/IInput.h>

#include "Statement.h"
#include "holder/Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

/*************************************************************************/
/** The Input class.
 *
 */
class Input :
		public virtual DS::API::IInput {
public:

	virtual ~Input() throw();

	virtual void addInput(const String& strTag, DM::Tools::Setter *pSetter);
	virtual void feedInputs(DM::DataObjectPtr& dm);

protected:
	Input(Statement& statement);

	Holder::Base::Table			   			     tabHolders;

	int iNum;
	Statement& statement;
};
/*************************************************************************/
}
}
}
}

#endif /* _IAS_DS_Impl_ODBC_Input_H_ */
