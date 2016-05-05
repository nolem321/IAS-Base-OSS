/*
 * File: IAS-CommonLib/src/commonlib/logger/LogLevel.h
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

#ifndef _IAS_LogLevel_H_
#define _IAS_LogLevel_H_


#include <iostream>

#define IAS_LOG_LEVEL_GLOBAL_ENV "IAS_DBG_GLOBAL"
#define IAS_LOG_LEVEL_COMMON_ENV "IAS_DBG_COMMONLIB"

namespace IAS{

/*************************************************************************/
/** The LogLevel class.
 */

class LogLevelBase {
public:
			
		inline bool isSystem()      { return this->bIsSystem;       };
		inline bool isError()       { return this->bIsError;        };
		inline bool isInfo()        { return this->bIsInfo;         };
		inline bool isDetailedInfo(){ return this->bIsDetailedInfo; };
		inline bool isTrace()       { return this->bIsTrace;        };
		inline bool isMemory()      { return this->bIsMemory;       };
		inline bool isDspMsg()      { return this->bIsDspMsg;           };
		inline bool isStackTrace()  { return this->bIsStackTrace;       };
		inline bool isMemoryTrace() { return this->bIsMemoryTrace;      };
		inline bool isProfile ()    { return this->bIsProfile;        };
		inline bool isExceptionThrow()       { return this->bIsExceptionThrow;      };
		inline bool isReportedExceptions()   { return this->bIsReportedExceptions; };
		inline bool isData()        { return this->bIsData;       };
	/*************************************************************************/	
		
		LogLevelBase(const char *sEnvVarName,
					 const char *sEnvSecondaryVarName = IAS_LOG_LEVEL_GLOBAL_ENV);
			
		virtual ~LogLevelBase();
	
/*************************************************************************/
 //TODO (L) protected ?
	 bool bIsSystem;
	 bool bIsError;
	 bool bIsInfo;
	 bool bIsDetailedInfo;
	 bool bIsTrace;
	 bool bIsMemory;
	 bool bIsDspMsg;
	 bool bIsStackTrace;	 
	 bool bIsException;
	 bool bIsReportedExceptions;
	 bool bIsExceptionThrow;
	 bool bIsMemoryTrace;
	 bool bIsProfile;
	 bool bIsData;
};

/*************************************************************************/

class LogLevel : public LogLevelBase {
	public:

	static LogLevelBase INSTANCE; // The global instance.
};


/*************************************************************************/



}/* namespace IAS */

#endif /*LOGGER_H_*/


