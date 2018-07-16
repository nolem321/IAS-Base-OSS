/*
 * File: IAS-QSystemMod-PostgreSQL/src/ds/Impl/PostgreSQL/log/LogLevel.cpp
 * 
 * Copyright (C) 2015, Albert Krzymowski
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "LogLevel.h"

#include <commonlib/commonlib.h>

#define IAS_LOG_LEVEL_DS_SQLITE_ENV "IAS_DBG_DS_SQLITE"

namespace IAS {
namespace DS {
namespace Impl {
namespace PostgreSQL {

/*************************************************************************/
LogLevelBase LogLevel::INSTANCE=LogLevelBase(IAS_LOG_LEVEL_DS_SQLITE_ENV);
/*************************************************************************/

}
}
}
}
