/*
 * File: IAS-QSystemLib/src/qs/workers/proc/io/IOManager.cpp
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
#include "IOManager.h"

namespace IAS {
namespace QS {
namespace Workers {
namespace Proc {
namespace IO {

/*************************************************************************/
IOManager::IOManager()throw():
	strDefaultInput("input"),
	strDefaultOutput("output"),
    strDefaultError("error"){};
/*************************************************************************/
void IOManager::setDefaultOutput(const String& strName){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"DefaultOutput: "<<strName);
	this->strDefaultOutput=strName;
}
/*************************************************************************/
void IOManager::setDefaultError(const String& strName){
	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"DefaultError: "<<strName);
	this->strDefaultError=strName;
}
/*************************************************************************/
void IOManager::setDefaultInput(const String& strName){
	IAS_TRACER
	IAS_LOG(LogLevel::INSTANCE.isInfo(),"DefaultInput: "<<strName);
	this->strDefaultInput=strName;
}
/*************************************************************************/
Output* IOManager::getDefaultOutput()const{
	return getOutput(strDefaultOutput);
}
/*************************************************************************/
Output* IOManager::getDefaultError()const{
	return getOutput(strDefaultError);
}
/*************************************************************************/
Input*  IOManager::getDefaultInput()const{
	return getInput(strDefaultInput);
}
/*************************************************************************/
}
}
}
}
}

