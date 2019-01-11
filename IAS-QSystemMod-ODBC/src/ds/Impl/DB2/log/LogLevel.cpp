/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/log/LogLevel.cpp 
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
#include "LogLevel.h"

#include <commonlib/commonlib.h>

#define IAS_LOG_LEVEL_DS_DB2_ENV "IAS_DBG_DS_DB2"

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
LogLevelBase LogLevel::INSTANCE=LogLevelBase(IAS_LOG_LEVEL_DS_DB2_ENV);
/*************************************************************************/

}
}
}
}
