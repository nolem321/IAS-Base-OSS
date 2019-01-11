/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/holder/Float.h 
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
#ifndef _IAS_DS_Impl_DB2_Holder_Float_H_
#define _IAS_DS_Impl_DB2_Holder_Float_H_

#include <commonlib/commonlib.h>

#include "Base.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {
namespace Holder {

/*************************************************************************/
/** The Float class.
 *
 */
class Float : public Base {
public:

	virtual ~Float() throw();

	virtual void fetch(DM::DataObjectPtr& dm);
	virtual void feed(DM::DataObjectPtr& dm);

protected:
	Float(Statement* pStatement,  DM::Tools::Setter* pSetter, bool bOptional);

	static const size_t CBufferLen=sizeof(SQLDOUBLE);

	friend class ::IAS::Factory<Float>;
};

/*************************************************************************/
}
}
}
}
}

#endif /* _IAS_DS_Impl_DB2_Holder_Float_H_ */
