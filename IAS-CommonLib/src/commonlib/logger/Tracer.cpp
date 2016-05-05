/*
 * File: IAS-CommonLib/src/commonlib/logger/Tracer.cpp
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

#include "Tracer.h"
#include "TracerStats.h"
#include "logger.h"

#include "time.h"
#include "sys/time.h"

#include "../types.h"

namespace IAS{

Tracer::Tracer(const char *sFun,
		       const char *sFile,
		       int        iLine):
		   ts(::IAS::LogLevel::INSTANCE.isProfile()){

	this->sFun=sFun;
	this->sFile=sFile;
	this->iLine=iLine;

	if(::IAS::LogLevel::INSTANCE.isStackTrace()){
		IAS_MY_STACK().addEntry(sFun, sFile, iLine);
	}

	IAS_ENTER_FUN(IAS::LogLevel::INSTANCE.isTrace(), sFun, sFile, iLine);

}

Tracer::~Tracer(){

	if(::IAS::LogLevel::INSTANCE.isProfile())
		TracerStats::GetInstance()->addEntry(sFile,sFun,ts);

	if(::IAS::LogLevel::INSTANCE.isStackTrace()){
		IAS_MY_STACK().removeEntry();
	}

	IAS_LEAVE_FUN(IAS::LogLevel::INSTANCE.isTrace(), sFun, sFile, iLine);
}

}

