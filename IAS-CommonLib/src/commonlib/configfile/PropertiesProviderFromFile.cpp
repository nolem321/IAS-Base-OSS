/*
 * File: IAS-CommonLib/src/commonlib/configfile/PropertiesProviderFromFile.cpp
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

#include "PropertiesProviderFromFile.h"
#include "../logger/logger.h"

#include "../exception/ConfigException.h"
#include "../exception/ItemNotFoundException.h"

#include <iostream>

namespace IAS
{

/*************************************************************************/
PropertiesProviderFromFile::PropertiesProviderFromFile(const char* sFileName):iLineNo(0)
{
	IAS_TRACER;
	openFile(sFileName);
}
/*************************************************************************/
PropertiesProviderFromFile::PropertiesProviderFromFile():iLineNo(0){};
/*************************************************************************/
PropertiesProviderFromFile::~PropertiesProviderFromFile()
{
	IAS_TRACER;
}
/*************************************************************************/

void PropertiesProviderFromFile::openFile(const char* sFileName){

	IAS_TRACER;
	IAS_LOG(LogLevel::INSTANCE.isSystem(), "Opening properties file:"<<"["<<sFileName<<"]");
	isFile.open(sFileName);
	if(! (isFile.good()) ){
		IAS_THROW(ConfigException(sFileName));
	}
}

/*************************************************************************/
void PropertiesProviderFromFile::getNextProperty(String& strName, String& strValue){
	IAS_TRACER;
	//TODO (LL) ladniejsza wersja PropertiesProviderFromFile
	char sLine[256];

	while(isFile.good()){

		isFile.getline(sLine, 255, '\n');
		iLineNo++;

		if(*sLine == '#')
			continue;

		String strLine(sLine);
		int iPos = strLine.find('=');

		if(iPos == String::npos){
			IAS_THROW(ConfigException("Missing '='",strFileName.c_str(),iLineNo));
		}

		strName=strLine.substr(0,iPos);
		strValue=strLine.substr(iPos+1);

		return;
	}

	IAS_THROW(ItemNotFoundException());
}

/*************************************************************************/
void PropertiesProviderFromFile::reset(){
	IAS_TRACER;
	isFile.clear();
	isFile.seekg(0,std::ios::beg);
	iLineNo=0;
}



}
