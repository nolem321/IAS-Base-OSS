/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexerForMemory.cpp
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
#include "../../dm/xml/LibXMLLexerForMemory.h"

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"
#include "../../dm/xml/LibXMLWrapper.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLLexerForMemory::LibXMLLexerForMemory(const String& strXML){
	IAS_TRACER;

	LibXMLWrapper::GetInstance();

	//TODO encoding & options
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"XML:"<<strXML.length()<<" bytes.");
	xmlTextReaderPtr pXMLTextReader =
			xmlReaderForMemory(strXML.c_str(),strXML.length(), NULL, NULL, 0);

	if(pXMLTextReader == NULL)
		IAS_THROW(XMLHelperException(String("Cannot create xmlReaderForMemory.")));

	setup(pXMLTextReader);
}
/*************************************************************************/
LibXMLLexerForMemory::~LibXMLLexerForMemory() throw(){
	IAS_TRACER;
}
/*************************************************************************/
}
}
}
