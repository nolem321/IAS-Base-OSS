/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexerForFile.cpp
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
#include "../../dm/xml/LibXMLLexerForFile.h"

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"
#include "../../dm/xml/LibXMLWrapper.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLLexerForFile::LibXMLLexerForFile(const String& strFileName){
	IAS_TRACER;

	LibXMLWrapper::GetInstance();

	//TODO encoding & options
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"Opening:"<<strFileName);
	xmlTextReaderPtr pXMLTextReader = xmlReaderForFile(strFileName.c_str(), NULL, 0);

	if(pXMLTextReader == NULL)
		IAS_THROW(XMLHelperException(String("Cannot open: ")+=strFileName));

	setup(pXMLTextReader);
}
/*************************************************************************/
LibXMLLexerForFile::~LibXMLLexerForFile() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
