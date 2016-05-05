/*
 * File: IAS-LangLib/src/lang/log/LogLevel.cpp
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
#include<lang/log/LogLevel.h>

#include <commonlib/commonlib.h>

#define IAS_LOG_LEVEL_LANG_ENV "IAS_DBG_LANG"

namespace IAS {
namespace Lang {

/*************************************************************************/
LogLevelBase LogLevel::INSTANCE=LogLevelBase(IAS_LOG_LEVEL_LANG_ENV);
/*************************************************************************/

}
}
