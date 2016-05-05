/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLWriter.cpp
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
#include "../../dm/xml/LibXMLWriter.h"
#include <commonlib/commonlib.h>
#include "dm/log/LogLevel.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLWriter::LibXMLWriter() throw():pXMLTextWriter(NULL){
	IAS_TRACER;
}
/*************************************************************************/
LibXMLWriter::~LibXMLWriter() throw(){
	IAS_TRACER;
	cleanUp();
}
/*************************************************************************/
void LibXMLWriter::cleanUp(){
	IAS_TRACER;

	if(pXMLTextWriter==NULL)
		return;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"xmlFreeTextWriter["<<(void*)pXMLTextWriter<<"]");
	xmlFreeTextWriter(pXMLTextWriter);
	pXMLTextWriter=NULL;
};
/*************************************************************************/
void LibXMLWriter::startDocument(const String& strVersion, const String& strEncoding){
	IAS_TRACER;

	int iRet = xmlTextWriterStartDocument(pXMLTextWriter,
										  (const char*) strVersion.c_str(),
										  (const char*) strEncoding.c_str(),
										  NULL);

	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterStartDocument failed."));

}
/*************************************************************************/
void LibXMLWriter::LibXMLWriter::endDocument(){
	IAS_TRACER;

	int iRet = xmlTextWriterEndDocument(pXMLTextWriter);
	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterEndDocument failed."));
}
/*************************************************************************/
void LibXMLWriter::startElement(const String& strElement){
	IAS_TRACER;

	int iRet = xmlTextWriterStartElement(pXMLTextWriter,
										 (const xmlChar*)strElement.c_str());

	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterStartElement failed."));

}
/*************************************************************************/
void LibXMLWriter::startElementNS(const String& strPrefix,
									  const String& strElement,
									  const String& strURI){
	IAS_TRACER;

	int iRet = xmlTextWriterStartElementNS(pXMLTextWriter,
										   (const xmlChar*)strPrefix.c_str(),
										   (const xmlChar*)strElement.c_str(),
										   (const xmlChar*)(strURI.empty() ? NULL :strURI.c_str()));


	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterStartElementNS failed."));

}
/*************************************************************************/
void LibXMLWriter::endElement(){
	IAS_TRACER;

	int iRet = xmlTextWriterEndElement(pXMLTextWriter);

	if(iRet == -1)
		IAS_THROW(XMLHelperException("endElement failed."));

}
/*************************************************************************/
void LibXMLWriter::writeElement(const String& strName,
									const String& strValue){
	IAS_TRACER;

	int iRet = xmlTextWriterWriteElement(pXMLTextWriter,
										 (const xmlChar*)strName.c_str(),
										 (const xmlChar*)strValue.c_str());

	if(iRet == -1)
		IAS_THROW(XMLHelperException("writeElement failed."));

}
/*************************************************************************/
void LibXMLWriter::writeElementNS(const String& strPrefix,
					  const String& strElement,
					  const String& strValue,
					  const String& strURI){
	IAS_TRACER;

	int iRet = xmlTextWriterWriteElementNS(pXMLTextWriter,
										 (const xmlChar*)strPrefix.c_str(),
										 (const xmlChar*)strElement.c_str(),
										 (const xmlChar*)strURI.c_str(),
										 (const xmlChar*)strValue.c_str());


	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterWriteElementNS failed."));
}

/*************************************************************************/
void LibXMLWriter::writeAttribute(const String& strName,
					  const String& strValue){
	IAS_TRACER;
	int iRet = xmlTextWriterWriteAttribute(pXMLTextWriter,
										 (const xmlChar*)strName.c_str(),
										 (const xmlChar*)strValue.c_str());


	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterWriteAttribute failed."));
}
/*************************************************************************/
void LibXMLWriter::writeAttributeNS(const String& strPrefix,
					    const String& strName,
					    const String& strValue,
					    const String& strURI){
	IAS_TRACER;
	int iRet = xmlTextWriterWriteAttributeNS(pXMLTextWriter,
										 (const xmlChar*)strPrefix.c_str(),
										 (const xmlChar*)strName.c_str(),
										 ! strURI.empty() ? (const xmlChar*)strURI.c_str() : NULL,
										 (const xmlChar*)strValue.c_str());


	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterWriteAttributeNS failed."));
}
/*************************************************************************/
void LibXMLWriter::writeString(const String& strValue){
	IAS_TRACER;
	int iRet = xmlTextWriterWriteString(pXMLTextWriter,
										 (const xmlChar*)strValue.c_str());


	if(iRet == -1)
		IAS_THROW(XMLHelperException("xmlTextWriterWriteString failed."));
}
/*************************************************************************/
void LibXMLWriter::init(xmlTextWriterPtr pXMLTextWriter){
	IAS_TRACER;


	this->pXMLTextWriter=pXMLTextWriter;

	const xmlChar s[2] = " ";
	xmlTextWriterSetIndent(pXMLTextWriter, 1);
	xmlTextWriterSetIndentString(pXMLTextWriter, s);

}
/*************************************************************************/
}
}
}
