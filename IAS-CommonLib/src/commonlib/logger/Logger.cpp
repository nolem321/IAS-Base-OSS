/*
 * File: IAS-CommonLib/src/commonlib/logger/Logger.cpp
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

#include "Logger.h"
#include "../threads/Thread.h"
#include "../memory/memory.h"

#include <iomanip>

#include "LoggerFileLock.h"

#include "StackTrace.h"
#include "StackTraceContainer.h"
#include <commonlib/tools/TypeTools.h>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <iterator>
#include <algorithm>

#include "outputs/FileSizeLimitedLogger.h"
#include "outputs/TimeLimitedLogger.h"

namespace IAS{

using namespace LoggerOutputs;

static LOGGER::LoggerFileLock _fileLock;
Logger* Logger::TheInstance = NULL;

const char* Logger::CEnvPrtPid("IAS_DBG_PRT_PID");
const char* Logger::CEnvPrtLoc("IAS_DBG_PRT_LOC");
const char* Logger::CEnvPrtRTS("IAS_DBG_PRT_RTS");

static inline bool _getBoolValue(const char* sEnv){
	return sEnv && getenv(sEnv) && getenv(sEnv)[0] == 'Y';
}
/*************************************************************************/
Logger::Logger():
		bPrintPID(_getBoolValue(CEnvPrtPid)),
		bPrintLoc(_getBoolValue(CEnvPrtLoc)),
		bPrintRTS(_getBoolValue(CEnvPrtRTS)),
		pos(NULL)
{
	setup(&std::cerr);
}
/*************************************************************************/
Logger::~Logger(){
}
/*************************************************************************/
void Logger::setup(std::ostream* pos){
	this->pos = pos;
}
/*************************************************************************/
inline void Logger::addEntryPrefix(const char* sFun,
					   			   const char* sFile,
					   			   int         iLine){

	rotateLogs();

	if (bPrintRTS) {

		std::stringstream ss;
		char buf[32];
		time_t tTime=time(0);
		struct tm tmpTime;
		localtime_r(&tTime,&tmpTime);


		ss<<std::setfill('0');
		ss<<std::setw(2)<<1900+(tmpTime.tm_year)<<"-";
		ss<<std::setw(2)<<(tmpTime.tm_mon)+1<<"-";
		ss<<std::setw(2)<<(tmpTime.tm_mday)<<" ";

		ss<<std::setw(2)<<(tmpTime.tm_hour)<<":";
		ss<<std::setw(2)<<(tmpTime.tm_min)<<":";
		ss<<std::setw(2)<<(tmpTime.tm_sec)<<" ";

		(*pos)<<ss.str();

	}


	if(bPrintLoc){

		if(bPrintPID){

			struct timespec ts;
		   ::clock_gettime(CLOCK_MONOTONIC, &ts);

		   (*pos).width(10);
		   (*pos)<<ts.tv_sec<<".";
		   (*pos).width(10);
		   (*pos).fill('0');
		   (*pos)<<ts.tv_nsec<<":";

		   (*pos).fill(' ');
		   (*pos).width(10);
		   (*pos)<<getpid()<<":";
		   (*pos).width(20);
		   (*pos)<<(long)pthread_self()<<":";

		}

		if(sFile && sFun){
		   (*pos).width(60);
		   (*pos)<<sFile;
		   (*pos)<<"(";
		   (*pos).width(4);
		   (*pos)<<iLine;
		   (*pos)<<"):";
		   (*pos).width(26);
		   (*pos)<<sFun;
		   (*pos)<<":";
		   (*pos).width(0);
		}

	}
		int iIndent = IAS_MY_STACK().getSize();

		static const std::string strSpaces("                                                               ");

		(*pos)<<strSpaces.substr(0,iIndent);
}


/*************************************************************************/
void  Logger::tokenize(const String& strInput, StringList& refOutput, char cDelimiter)  const {

	size_t iStart = 0;
	size_t iCursor = 0;

	refOutput.clear();
	while (iCursor != String::npos) {

		iCursor = strInput.find(cDelimiter, iStart);

		if (iCursor == String::npos){
			refOutput.push_back(strInput.substr(iStart, String::npos));
		} else {
			refOutput.push_back(strInput.substr(iStart, iCursor - iStart));
			iStart = iCursor+1;
		}

	}
}
/*************************************************************************/
void Logger::rotateLogs(){
}
/*************************************************************************/
void Logger::addEntry(const char* sFun,
					  const char* sFile,
				 	  int         iLine,
				 	  const char* sText){

	StringList lstLines;
	tokenize(sText,lstLines,'\n');

	LOGGER::LoggerFileLock::Locker locker(_fileLock);

	/* The most important thing in pthreads. When
	 * cancellation point happens in std::cerr ostream is set as not good.
	 */

	Thread::Cancellation tc(false);

	if(!pos->good())
		pos->clear();

	for(StringList::const_iterator it=lstLines.begin();
			it != lstLines.end(); it++){

		addEntryPrefix(sFun,sFile,iLine);
		(*pos)<<" "<<(*it)<<"\n";
	}

	(*pos).flush();

}
/*************************************************************************/
void Logger::addEntry(const char* sText){
	addEntry(NULL,NULL,0,sText);
}
/*************************************************************************/
Logger* Logger::GetInstance(){

	if (!TheInstance) {

		if(getenv(TimeLimitedLogger::CEnvPeriod))
			TheInstance = new TimeLimitedLogger();
		else if(getenv(FileSizeLimitedLogger::CEnvFileBasename))
			TheInstance = new FileSizeLimitedLogger();
		else
			TheInstance = new Logger();
	}

	return TheInstance;
}
/*************************************************************************/
}/*namespace IAS */
