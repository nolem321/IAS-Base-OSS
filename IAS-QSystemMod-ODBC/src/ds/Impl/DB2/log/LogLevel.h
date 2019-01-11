/*
 * Copyright (C) 2015, Albert Krzymowski
 * Copyright (C) 2015, Invenire Aude Limited
 *
 * File: IAS-QSystemMod-DB2/src/ds/Impl/DB2/log/LogLevel.h 
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
#ifndef _IAS_DS_DB2_LogLevel_H_
#define _IAS_DS_DB2_LogLevel_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace DB2 {

/*************************************************************************/
/** The LogLevel class.
 *
 */
class LogLevel : public LogLevelBase {
public:

	static LogLevelBase INSTANCE;
};

/*************************************************************************/
}
}
}
}

#endif /* _IAS_DM_LogLevel_H_ */
