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

#include "LoggerFileLock.h"

#include "StackTrace.h"
#include "StackTraceContainer.h"
#include <commonlib/tools/TypeTools.h>
#include <unistd.h>

namespace IAS{

static LOGGER::LoggerFileLock _fileLock;

static bool  _bPrintPID(getenv("IAS_DBG_PRT_PID"));
static bool  _bPrintLoc(getenv("IAS_DBG_PRT_LOC"));
Logger* Logger::TheInstance = NULL;

/*************************************************************************/
Logger::Logger(){
	pos=&std::cerr;
}

/*************************************************************************/
Logger::~Logger(){
}

/*************************************************************************/
inline void Logger::addEntryPrefix(const char* sFun,
					   			   const char* sFile,
					   			   int         iLine){

	if(_bPrintLoc){

		if(_bPrintPID){

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
		int iIndent = IAS_MY_STACK().getSize();

		static const std::string strSpaces("                                                               ");

		(*pos)<<strSpaces.substr(0,iIndent);
}


/*************************************************************************/
static void  _tokenize(const String& strInput, StringList& refOutput, char cDelimiter) {

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
void Logger::addEntry(const char* sFun,
					  const char* sFile,
				 	  int         iLine,
				 	  const char* sText){
	
	LOGGER::LoggerFileLock::Locker locker(_fileLock);

	/* The most important thing in pthreads. When
	 * cancellation point happens in std::cerr ostream is set as not good.
	 */

	Thread::Cancellation tc(false);

	if(!pos->good())
		pos->clear();

	StringList lstLines;
	_tokenize(sText,lstLines,'\n');

	for(StringList::const_iterator it=lstLines.begin();
			it != lstLines.end(); it++){

		addEntryPrefix(sFun,sFile,iLine);
		(*pos)<<" "<<(*it)<<"\n";
	}
		(*pos).flush();
	//usleep(10000);
}

}/*namespace IAS */
