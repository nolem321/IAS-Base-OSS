/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWrapper.cpp
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
#include "../../dm/xml/LibXMLWrapper.h"
#include <commonlib/commonlib.h>

#include <libxml/xmlreader.h>

#include "../../dm/log/LogLevel.h"

namespace IAS {
namespace DM {
namespace XML {

//template<>
//IAS::InstanceFeature<LibXMLWrapper>::TheInstanceType IAS::InstanceFeature<LibXMLWrapper>::TheInstance(NULL);

/*************************************************************************/
LibXMLWrapper::LibXMLWrapper(){
	IAS_TRACER;

	//TODO thread safety

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"LibXml2 will be initialized.");

		LIBXML_TEST_VERSION;

		hmNodes[XML_READER_TYPE_NONE]=": XML_READER_TYPE_NONE";
		hmNodes[XML_READER_TYPE_ELEMENT]=": XML_READER_TYPE_ELEMENT";
		hmNodes[XML_READER_TYPE_ATTRIBUTE]=": XML_READER_TYPE_ATTRIBUTE";
		hmNodes[XML_READER_TYPE_TEXT]=": XML_READER_TYPE_TEXT";
		hmNodes[XML_READER_TYPE_CDATA]=": XML_READER_TYPE_CDATA";
		hmNodes[XML_READER_TYPE_ENTITY_REFERENCE]=": XML_READER_TYPE_ENTITY_REFERENCE";
		hmNodes[XML_READER_TYPE_ENTITY]=": XML_READER_TYPE_ENTITY";
		hmNodes[XML_READER_TYPE_PROCESSING_INSTRUCTION]=": XML_READER_TYPE_PROCESSING_INSTRUCTION";
		hmNodes[XML_READER_TYPE_COMMENT]=": XML_READER_TYPE_COMMENT";
		hmNodes[XML_READER_TYPE_DOCUMENT]=": XML_READER_TYPE_DOCUMENT";
		hmNodes[XML_READER_TYPE_DOCUMENT_TYPE]=": XML_READER_TYPE_DOCUMENT_TYPE";
		hmNodes[XML_READER_TYPE_DOCUMENT_FRAGMENT]=": XML_READER_TYPE_DOCUMENT_FRAGMENT";
		hmNodes[XML_READER_TYPE_NOTATION]=": XML_READER_TYPE_NOTATION";
		hmNodes[XML_READER_TYPE_WHITESPACE]=": XML_READER_TYPE_WHITESPACE";
		hmNodes[XML_READER_TYPE_SIGNIFICANT_WHITESPACE]=": XML_READER_TYPE_SIGNIFICANT_WHITESPACE";
		hmNodes[XML_READER_TYPE_END_ELEMENT]=": XML_READER_TYPE_END_ELEMENT";
		hmNodes[XML_READER_TYPE_END_ENTITY]=": XML_READER_TYPE_END_ENTITY";
		hmNodes[XML_READER_TYPE_XML_DECLARATION]=": XML_READER_TYPE_XML_DECLARATION";


		IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"LibXml2 has been initialized.");
}
/*************************************************************************/
LibXMLWrapper::~LibXMLWrapper() throw(){
	IAS_TRACER;
	xmlCleanupParser();
}
/*************************************************************************/
const char* LibXMLWrapper::getNodeName(int iNode) const{
	IAS_TRACER;

	NodesMap::const_iterator it=hmNodes.find(iNode);

	if(it == hmNodes.end()) {
		StringStream ssInfo;
		ssInfo<<"Unknown libxml node type: "<<iNode;
		IAS_THROW(ItemNotFoundException(ssInfo.str()));
	}

	return it->second;

}
/*************************************************************************/
}
}
}
