/*
 * File: IAS-QSystemMod-SQLite/src/ds/Impl/SQLite/log/LogLevel.h
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
#ifndef _IAS_DS_SQLite_LogLevel_H_
#define _IAS_DS_SQLite_LogLevel_H_

#include <commonlib/commonlib.h>

namespace IAS {
namespace DS {
namespace Impl {
namespace SQLite {

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
