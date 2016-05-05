/*
 * File: IAS-CommonLib/src/commonlib/logger/LogLevelHelper.cpp
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

/*
 * Do not use the STL and other advanced structures here as they may not be initialized properly.
 * For the same reason we do not report errors and log anything here.
 */

#include "../types.h"
#include "../memory/memory.h"
#include <iostream>

#include "LogLevel.h"
#include "LogLevelHelper.h"

#include <string.h>

#define IAS_LOGLEVEL_MAXWORD_LEN 32
#define IAS_DBGLEVEL_CHECKWORD(w,s,v) \
	if(strncmp(sWord,(w),IAS_LOGLEVEL_MAXWORD_LEN)==0) \
	ptrLogLevel->s        = (v);

namespace IAS{

void LogLevelHelper::ReadWordSettings(LogLevelBase   *ptrLogLevel, const char *sWord){

	if(ptrLogLevel == NULL || sWord == NULL)
		return;	

	IAS_DBGLEVEL_CHECKWORD("+system",  bIsSystem,    true);
	IAS_DBGLEVEL_CHECKWORD("-system",  bIsSystem,    false);

	IAS_DBGLEVEL_CHECKWORD("+error",  bIsError,    true);
	IAS_DBGLEVEL_CHECKWORD("-error",  bIsError,    false);

	IAS_DBGLEVEL_CHECKWORD("+info",  bIsInfo,    true);
	IAS_DBGLEVEL_CHECKWORD("-info",  bIsInfo,    false);

	IAS_DBGLEVEL_CHECKWORD("+details",  bIsDetailedInfo,    true);
	IAS_DBGLEVEL_CHECKWORD("-details",  bIsDetailedInfo,    false);

	IAS_DBGLEVEL_CHECKWORD("+trace",  bIsTrace,    true);
	IAS_DBGLEVEL_CHECKWORD("-trace",  bIsTrace,    false);

	IAS_DBGLEVEL_CHECKWORD("+memory",  bIsMemory,    true);
	IAS_DBGLEVEL_CHECKWORD("-memory",  bIsMemory,    false);

	IAS_DBGLEVEL_CHECKWORD("+msgs",  bIsDspMsg,    true);
	IAS_DBGLEVEL_CHECKWORD("-msgs",  bIsDspMsg,    false);

	IAS_DBGLEVEL_CHECKWORD("+stacktrace",  bIsStackTrace,    true);
	IAS_DBGLEVEL_CHECKWORD("-stacktrace",  bIsStackTrace,    false);
	
	IAS_DBGLEVEL_CHECKWORD("+throw",  bIsExceptionThrow,    true);
	IAS_DBGLEVEL_CHECKWORD("-throw",  bIsExceptionThrow,    false);

	IAS_DBGLEVEL_CHECKWORD("+reportedexception",  bIsReportedExceptions,    true);
	IAS_DBGLEVEL_CHECKWORD("-reportedexception",  bIsReportedExceptions,    false);

	IAS_DBGLEVEL_CHECKWORD("+memorytrace",  bIsMemoryTrace,    true);
	IAS_DBGLEVEL_CHECKWORD("-memorytrace",  bIsMemoryTrace,    false);

	IAS_DBGLEVEL_CHECKWORD("+profile",  bIsProfile,    true);
	IAS_DBGLEVEL_CHECKWORD("-profile",  bIsProfile,    false);

	IAS_DBGLEVEL_CHECKWORD("+data",  bIsData,    true);
	IAS_DBGLEVEL_CHECKWORD("-data",  bIsData,    false);

}

/*************************************************************************/
void LogLevelHelper::ReadSettings(LogLevelBase   *ptrLogLevel,
								  const char *sSettings){
	
	if(ptrLogLevel == NULL || sSettings == NULL)
		return;
	
	int iIdx;
	char sBuffer[IAS_LOGLEVEL_MAXWORD_LEN + 1];
	char *sCur;
	
	while(*sSettings != 0){
		
		iIdx = 0;
		sCur=sBuffer;
		
		while(*sSettings != 0 && *sSettings != ','){		
		
			if(iIdx < IAS_LOGLEVEL_MAXWORD_LEN)
				*(sCur++)=*sSettings;			
				
			iIdx++;
			sSettings++;
		
		}/* WHILE: */
				
		*sCur = 0;
		
		if(*sSettings == ',')
			sSettings++;
		
		if(iIdx > 0 && iIdx < IAS_LOGLEVEL_MAXWORD_LEN)
			ReadWordSettings(ptrLogLevel, sBuffer);
	
	}/* WHILE */	
}

/*************************************************************************/
void LogLevelHelper::SetDefaults(LogLevelBase   *ptrLogLevel){

	if(ptrLogLevel == NULL)
		return;

	ptrLogLevel->bIsSystem         = false;
	ptrLogLevel->bIsError          = true;
	ptrLogLevel->bIsInfo           = false;
	ptrLogLevel->bIsDetailedInfo   = false;
	ptrLogLevel->bIsTrace          = false;
	ptrLogLevel->bIsMemory         = false;
	ptrLogLevel->bIsStackTrace     = false;
	ptrLogLevel->bIsExceptionThrow = false;
	ptrLogLevel->bIsDspMsg         = true;		   
	ptrLogLevel->bIsReportedExceptions     = true;


}
}/*namespace IAS */

