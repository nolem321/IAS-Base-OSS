/*
 * File: IAS-CommonLib/src/commonlib/logger/FileLogger.h
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

#ifndef _IAS_FileLogger_H_
#define _IAS_FileLogger_H_

#include "../Logger.h"

namespace IAS{
namespace LoggerOutputs {

/*************************************************************************/
/** The FileLogger class.
 */

class FileLogger : public ::IAS::Logger {

public:

	virtual ~FileLogger();

	static const char* CEnvFileBasename;

protected:

	FileLogger();
	void openLogFile();

	std::fstream ofLog;
	const char *sLogBasename;

};

}
}

#endif /*_IAS_FileLogger_H_*/

