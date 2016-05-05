/*
 * File: IAS-CommonLib/src/commonlib/streams/OutputFile.cpp
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
#include "OutputFile.h"
#include "../exception/InternalException.h"
#include "commonlib/exception/ItemNotFoundException.h"

#include "../memory/memory.h"

namespace IAS {

/*************************************************************************/
OutputFile::OutputFile(const String& strName):File(strName){
	IAS_TRACER;
	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),"Create OutputFile for:["<<strName<<"]");
}

/*************************************************************************/
OutputFile::~OutputFile() {
	IAS_TRACER;
	close();
}

/*************************************************************************/
void OutputFile::open() {
	IAS_TRACER;
	os.open(strName.c_str());

	if(!isOpenedAndGood())
			IAS_THROW(SystemException(strName));

	IAS_LOG(IAS::LogLevel::INSTANCE.isInfo(),strName<<" - Is good !");

}
/*************************************************************************/
void OutputFile::close() {
	IAS_TRACER;
	os.close();
}

/*************************************************************************/
std::ofstream& OutputFile::getStreamRef(){
	IAS_TRACER;
	if(!os.good()){
		IAS_THROW(InternalException("file not opened."));
	}
	return os;
}

/*************************************************************************/
bool OutputFile::isOpenedAndGood(){
	IAS_TRACER;
	return os.good();
}

/*************************************************************************/
void OutputFile::SaveString(const String& strFileName, const String& strValue){
	IAS_TRACER;

	OutputFile of(strFileName);
	of.open();

	if(of.isOpenedAndGood())
		of.getStreamRef()<<strValue;

	of.close();
}
/*************************************************************************/
}
