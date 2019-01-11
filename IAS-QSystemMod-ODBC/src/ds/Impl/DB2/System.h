/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/System.h 
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
#ifndef _IAS_DS_DB2_System_H_
#define _IAS_DS_DB2_System_H_

#include <commonlib/commonlib.h>

#include <ds/api.h>
#include <ds/Impl/System.h>

#include "log/LogLevel.h"

#include <sqlcli1.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

class ContentManager;

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The DB2 class.
 *
 */
class System : public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	inline SQLHANDLE getEnvHandle(){ return henv; }

protected:

	System();

	SQLHANDLE henv;

	friend class Factory<System>;
};
/*************************************************************************/

}
}
}
}

#endif /* _IAS_DS_DB2_System_H_ */
