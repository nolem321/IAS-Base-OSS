/*
 * File: IAS-CommonLib/src/commonlib/streams/InputFile.cpp
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
#include "InputFile.h"

#include "commonlib/exception/InternalException.h"
#include "commonlib/exception/ItemNotFoundException.h"

#include "../memory/memory.h"

#include <commonlib/tools/MiscTools.h>

#include <iostream>
#include <fstream>
#include <string>

namespace IAS {

/*************************************************************************/
InputFile::InputFile(const String& strName):File(strName){
	IAS_TRACER;

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Create InputFile for:["<<strName<<"]");

}
/*************************************************************************/
InputFile::~InputFile() {
	IAS_TRACER;
	close();
}

/*************************************************************************/
void InputFile::open() {
	IAS_TRACER;
	IAS_LOG(IAS::LogLevel::INSTANCE.isSystem(),"["<<strName<<"]");
	is.open(strName.c_str());

	//TODO (L) system exception is it used somehwere ?

	if(!isOpenedAndGood())
		IAS_THROW(SystemException(strName));

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Is good !");
}

/*************************************************************************/
void InputFile::close() {
	IAS_TRACER;
	is.close();
}

/*************************************************************************/
std::istream& InputFile::getStreamRef(){
	IAS_TRACER;
	if(!is.good()){
		IAS_THROW(InternalException(String("File not opened: ")+=strName));
	}
	return is;
}

/*************************************************************************/
bool InputFile::isOpenedAndGood(){
	IAS_TRACER;
	return is.good() && is.is_open();
}
/*************************************************************************/
void InputFile::LoadString(const String& strFileName, String& strValue){
	IAS_TRACER;

	InputFile file(strFileName);
	file.open();

	StringStream ssTmp;

	MiscTools::CopyStreams(file.getStreamRef(),ssTmp);

	strValue=ssTmp.str();

}
/*************************************************************************/
void InputFile::LoadStdin(String& strValue){
	IAS_TRACER;

	StringStream ssInput;
	const int C_BlockSize=4096;

	char sBuffer[C_BlockSize+1];

	while(std::cin.good()){
		std::cin.read(sBuffer,C_BlockSize);
		sBuffer[std::cin.gcount()]=0;
		ssInput<<sBuffer;
	}

	strValue=ssInput.str();
}
/*************************************************************************/
}
