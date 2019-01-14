/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/holder/Date.h 
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
#ifndef _IAS_DS_Impl_ODBC_Holder_Date_H_
#define _IAS_DS_Impl_ODBC_Holder_Date_H_

#include <commonlib/commonlib.h>

#include "Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {
namespace Holder {

/*************************************************************************/
/** The Date class.
 *
 */
class Date : public Base {
public:

	virtual ~Date() throw();

	virtual void fetch(DM::DataObjectPtr& dm);
	virtual void feed(DM::DataObjectPtr& dm);

protected:
	Date(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	static const size_t CBufferLen=sizeof(DATE_STRUCT);

	friend class ::IAS::Factory<Date>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_ODBC_Holder_Date_H_ */
