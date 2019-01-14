/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-ODBC/src/ds/Impl/ODBC/System.h
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
#ifndef _IAS_DS_ODBC_System_H_
#define _IAS_DS_ODBC_System_H_

#include <commonlib/commonlib.h>

#include <ds/api.h>
#include <ds/Impl/System.h>

#include "log/LogLevel.h"

#include "tools/Handle.h"

namespace IAS {
namespace DS {
namespace Impl {
namespace ODBC {

class ContentManager;

class InputDriver;
class OutputDriver;

/*************************************************************************/
/** The ODBC class.
 *
 */
class System : public Impl::System {
public:

	virtual ~System() throw();

	virtual API::Connection* createConnection(const ::org::invenireaude::qsystem::workers::ds::Parameter* dmParameter);

	inline Tools::HandleEnv& getEnvHandle(){ return handleEnv; }

protected:

	System();

	Tools::HandleEnv handleEnv;

	friend class Factory<System>;
};
/*************************************************************************/

}
}
}
}

#endif /* _IAS_DS_ODBC_System_H_ */
