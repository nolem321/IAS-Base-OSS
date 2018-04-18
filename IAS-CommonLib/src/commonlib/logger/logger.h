/*
 * File: IAS-CommonLib/src/commonlib/logger/logger.h
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

#ifndef IASLOGGER_H_
#define IASLOGGER_H_

#include "./LogLevel.h"
#include "./Logger.h"
#include "./Tracer.h"
#include "./StackTrace.h"
#include "./StackTraceContainer.h"

#include <sstream>
#include <string>

#ifdef __IAS_NO_TRACER__
#define IAS_TRACER
#else
#define IAS_TRACER IAS::Tracer _IAS_tracer(__FUNCTION__,__FILE__,__LINE__);
#endif

#define IAS_LOG(i,s)              \
 if(i){ \
	std::stringstream ss; ss<<s;       \
	IAS::Logger::GetInstance()->addEntry(__FUNCTION__,__FILE__,__LINE__,ss.str().c_str()); \
	};       

#define IAS_ENTER_FUN(i,sFun,sFile,iLine)                      \
 if(i){                              \
    IAS::Logger::GetInstance()->addEntry(sFun,sFile,iLine,(">> Entering")); \
	};       

#define IAS_LEAVE_FUN(i,sFun,sFile,iLine)                      \
 if(i){                              \
	IAS::Logger::GetInstance()->addEntry(sFun,sFile,iLine,(">> Leaving")); \
	};       

#define IAS_THROW(e)              \
  {IAS_LOG(::IAS::LogLevel::INSTANCE.isExceptionThrow(),"Exception !!!"); \
   throw e; }
 

#define IAS_REPORT_EXCEPTION(e)                         \
{  if(::IAS::LogLevel::INSTANCE.isReportedExceptions()){  \
	 IAS::Logger::GetInstance()->addEntry(__FUNCTION__,__FILE__,__LINE__,e.toString().c_str()); \
	}; \
 }



#endif /*IASTYPES_H_*/
