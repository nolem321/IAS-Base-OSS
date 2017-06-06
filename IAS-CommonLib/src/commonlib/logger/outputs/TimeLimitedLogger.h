/*
 * File: IAS-CommonLib/src/commonlib/logger/TimeLimitedLogger.h
 * 
 * Copyright (C) 2017, Albert Krzymowski
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef _IAS_Logger_TimeLimitedLogger_H_
#define _IAS_Logger_TimeLimitedLogger_H_

#include "FileLogger.h"

namespace IAS{
namespace LoggerOutputs {


/*************************************************************************/
/** The TimeLimitedLogger class.
 */

class TimeLimitedLogger : public ::IAS::LoggerOutputs::FileLogger {

public:

	virtual ~TimeLimitedLogger();

	static const char* CEnvPeriod;
	TimeLimitedLogger();

private:

	size_t iPeriod;
	time_t tLastUpdate;

	virtual void rotateLogs();
	void openLogFile();

};

}
}
#endif /*_IAS_Logger_TimeLimitedLogger_H_*/

