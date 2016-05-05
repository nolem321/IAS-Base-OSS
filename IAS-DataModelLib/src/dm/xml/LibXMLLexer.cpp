/*
 * File: IAS-DataModelLib/src/dm/xml/LibXMLLexer.cpp
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
#include "../../dm/xml/LibXMLLexer.h"
#include <commonlib/commonlib.h>

#include <libxml/xmlreader.h>
#include "dm/log/LogLevel.h"

#include "../../dm/log/LogLevel.h"
#include "../../dm/xml/exception/XMLHelperException.h"
#include "../../dm/xml/LibXMLWrapper.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
LibXMLLexer::LibXMLLexer():
		bReadingAttributes(false),
		bSkipSignificantWhiteSpaces(false),
		pXMLTextReader(0){

	IAS_TRACER;
}
/*************************************************************************/
LibXMLLexer::~LibXMLLexer() throw(){
	IAS_TRACER;
	if(pXMLTextReader){
		xmlTextReaderClose(pXMLTextReader);
		xmlFreeTextReader(pXMLTextReader);
	}
}
/*************************************************************************/
void LibXMLLexer::setup(xmlTextReaderPtr pXMLTextReader){

	IAS_TRACER;

	this->pXMLTextReader = pXMLTextReader;
	xmlTextReaderSetErrorHandler(pXMLTextReader, (xmlTextReaderErrorFunc)_libxml_onError, this);
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"LibXMLLexer is ready.");

}

/*************************************************************************/
bool LibXMLLexer::isEmpty(){
	IAS_TRACER;

	if(bReadingAttributes){
		if(!xmlTextReaderMoveToElement(pXMLTextReader))
			IAS_THROW(XMLHelperException("Error when moving to an element."));
	}

	bReadingAttributes = false;
	return xmlTextReaderIsEmptyElement(pXMLTextReader);
}
/*************************************************************************/
bool LibXMLLexer::nextElement(){
	IAS_TRACER;

	if(bReadingAttributes){
		if(!xmlTextReaderMoveToElement(pXMLTextReader))
			IAS_THROW(XMLHelperException("Error when moving to an element."));
	}

	bReadingAttributes = false;

	do{

		int iRet = xmlTextReaderRead(pXMLTextReader);

		if(iRet == 0)
			return false;

		if(iRet != 1)
			IAS_THROW(XMLHelperException(strError));

	}while(bSkipSignificantWhiteSpaces &&
			(getType() == XML_READER_TYPE_SIGNIFICANT_WHITESPACE ||
			 getType() == XML_READER_TYPE_COMMENT));

	processNode();

	return true;
}
/*************************************************************************/
bool LibXMLLexer::nextAttribute(){
	IAS_TRACER;

	int iRet = xmlTextReaderMoveToNextAttribute(pXMLTextReader);

	if(iRet == 0)
		return false;

	if(iRet != 1)
		IAS_THROW(XMLHelperException(strError));

	processNode();
	bReadingAttributes = true;
	return true;
}
/*************************************************************************/
bool LibXMLLexer::moveToAttribute(const String& strAttrName){
	IAS_TRACER;

	int iRet = xmlTextReaderMoveToAttribute(pXMLTextReader, (const xmlChar*) strAttrName.c_str());

	if(iRet == 0)
		return false;

	if(iRet != 1)
		IAS_THROW(XMLHelperException(strError));

	processNode();
	bReadingAttributes = true;

	return true;
}
/*************************************************************************/
bool LibXMLLexer::moveToAttribute(int iIdx){
	IAS_TRACER;

	int iRet = xmlTextReaderMoveToAttributeNo(pXMLTextReader,iIdx);

	if(iRet == 0)
		return false;

	if(iRet != 1)
		IAS_THROW(XMLHelperException(strError));

	processNode();
	bReadingAttributes = true;

	return true;
}
/*************************************************************************/
const char* LibXMLLexer::getMandatoryAttribute(const String& strName){
	IAS_TRACER;

	if(!moveToAttribute(strName)){
		StringStream ssInfo;
		ssInfo<<"Missing attribute:"<<strName;
		IAS_THROW(XMLHelperException(ssInfo.str()));
	}

	return getValue();
}
/*************************************************************************/
bool LibXMLLexer::getOptionalAttribute(const String& strName, String& strValue){
	IAS_TRACER;

	if(!moveToAttribute(strName))
		return false;

	strValue=getValue();
	return true;
}
/*************************************************************************/
void LibXMLLexer::getPrefixWithURI(String& strPrefix, String& strURI){
	IAS_TRACER;

	const xmlChar *sPrefix = xmlTextReaderConstPrefix(pXMLTextReader);

	if(sPrefix!=NULL)
		strPrefix=(const char*)sPrefix;

	const xmlChar *sURI = xmlTextReaderConstNamespaceUri(pXMLTextReader);

	if(sURI!=NULL)
		strURI=(const char*)sURI;

}
/*************************************************************************/
void LibXMLLexer::processNode(){
	IAS_TRACER;
	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Node:["<<getName()<<"] of"
				<<LibXMLWrapper::GetInstance()->getNodeName(getType()));
}
/*************************************************************************/
void LibXMLLexer::setSkipSignificantWhiteSpaces(bool bSkipSignificantWhiteSpaces){
	IAS_TRACER;
	this->bSkipSignificantWhiteSpaces=bSkipSignificantWhiteSpaces;
}
/*************************************************************************/
void LibXMLLexer::_libxml_onError	(void* pArg,
							     const char * sMsg,
							     xmlParserSeverities severity,
						         xmlTextReaderLocatorPtr locator){
	LibXMLLexer* pLibXMLLexer = (LibXMLLexer*)pArg;
	IAS_CHECK_IF_VALID(pLibXMLLexer);
	pLibXMLLexer->onError(sMsg,severity,locator);
}
/*************************************************************************/
void  LibXMLLexer::onError	(const char * sMsg,
						 xmlParserSeverities severity,
						 xmlTextReaderLocatorPtr locator){

  IAS_TRACER;

  StringStream ssXMLInfo;
  ssXMLInfo<<"XML Error:"<<sMsg<<", severity: "<<severity<<", at: "<<(long)locator<<".";
  strError=ssXMLInfo.str();
}

/*************************************************************************/
void LibXMLLexer::ChopOffPrefix(const String& strValue,
							String &strPrefix,
							String& strBaseValue){
	IAS_TRACER;

	size_t iPos = strValue.find_first_of(':');

	if(iPos != String::npos){
		strPrefix = strValue.substr(0,iPos);
		strBaseValue = strValue.substr(iPos+1);
	}else{
		strBaseValue = strValue;
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),
			"["<<strPrefix<<"]["<<strBaseValue<<"]");

}
/*************************************************************************/
}
}
}
