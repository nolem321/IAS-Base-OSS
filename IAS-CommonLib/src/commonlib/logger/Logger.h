/*
 * File: IAS-CommonLib/src/commonlib/logger/Logger.h
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
/* IAS_COPYRIGHT */

/* ChangeLog:
 *
 */

#ifndef _IAS_Logger_H_
#define _IAS_Logger_H_

#include "../types.h"

#include <iostream>
#include <map>
#include <fstream>
namespace IAS{

/*************************************************************************/
/** The Logger class.
 */

class Logger {

public:

	Logger();
	virtual ~Logger();

	void addEntry(const char* sFun,
				  const char* sFile,
				  int         iLine,
				  const char* sText);

	static inline Logger* GetInstance(){
		if(!TheInstance){
			TheInstance = new Logger();
		}
		return TheInstance;
	};

private:
	static Logger* TheInstance;
	std::ostream* pos;

	void addEntryPrefix(const char* sFun,
						const char* sFile,
						int         iLine);

	std::fstream ofLog;
	size_t iLogLines;
	size_t iLogMaxLines;
	int    iNumLogs;
	bool  bPrintPID;
	bool  bPrintLoc;
	bool  bPrintRTS;

	const char *sLogBasename;

	void tokenize(const String& strInput, StringList& refOutput, char cDelimiter)  const;
	void rotateLogs()const;
	void openLogFile();
};

}

#endif /*LOGGER_H_*/

