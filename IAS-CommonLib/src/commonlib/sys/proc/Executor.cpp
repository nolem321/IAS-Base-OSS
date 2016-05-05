/*
 * File: IAS-CommonLib/src/commonlib/sys/proc/Executor.cpp
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
#include "Executor.h"

#include <commonlib/commonlib.h>

#include <stdlib.h>
#include <unistd.h>

namespace IAS {
namespace SYS {
namespace Proc {

/*************************************************************************/
Executor::Executor(const String& strCommand):strCommand(strCommand){
	IAS_TRACER;
}
/*************************************************************************/
Executor::~Executor() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Executor::appendArg(const String& strArg){
	IAS_TRACER;
	lstArgs.push_back(strArg);
}
/*************************************************************************/
void Executor::run(){
	IAS_TRACER;

	const char* *argv = (const char**)malloc((2+lstArgs.size())*sizeof(const char*));

	if(lstArgs.size() > 16)
		IAS_THROW(InternalException("lstArgs.size > 16"));

	argv[0]=strCommand.c_str();
	int iIdx = 1;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Will execute: "<<strCommand);

	for(ArgsList::const_iterator it = lstArgs.begin();
		it != lstArgs.end();
	    it++,iIdx++){
		argv[iIdx] = (*it).c_str();
		IAS_LOG(LogLevel::INSTANCE.isInfo(),"argv["<<iIdx<<"]="<<(*it));
	}

	argv[iIdx]=NULL;

	IAS_LOG(LogLevel::INSTANCE.isInfo(),"Execv !!!");
	int iRes = ::execvp(argv[0],(char* const*)argv);

	free(argv);
	IAS_THROW(SystemException(String("execv: [")+strCommand+"]",errno));
}
/*************************************************************************/
}
}
}
