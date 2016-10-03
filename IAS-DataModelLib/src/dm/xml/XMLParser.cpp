/*
 * File: IAS-DataModelLib/src/dm/xml/XMLParser.cpp
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
#include "../../dm/xml/XMLParser.h"
#include <commonlib/commonlib.h>


#include "../../dm/DataFactory.h"
#include "../../dm/DataObject.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/Type.h"
#include "../../dm/xml/LibXMLLexer.h"
#include "../../dm/xml/LibXMLWrapper.h"
#include "../../dm/xml/XMLDocument.h"
#include "../../dm/xml/XMLHelper.h"

namespace IAS {
namespace DM {
namespace XML {

/*************************************************************************/
XMLParser::XMLParser(XMLHelper* pXMLHelper, LibXMLLexer *pLibXMLLexer){
	IAS_TRACER;
	this->pXMLHelper=pXMLHelper;
	this->ptrLibXMLLexer=pLibXMLLexer;
	pDataFactory=pXMLHelper->getDataFactory();
}
/*********************************XMLParser****************************************/
XMLParser::~XMLParser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void XMLParser::parse_xml_element(DataObject* pParent){
	IAS_TRACER;

	String strType;
	String strName = ptrLibXMLLexer->getLocalName();
	String strPrefix;
	String strPrefixURI;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<":"<<(pParent==NULL ? "null" : pParent->getType()->getName()));

	const ::IAS::DM::Type* pType(NULL);
	const ::IAS::DM::Property *pProperty(NULL);

	ptrLibXMLLexer->getPrefixWithURI(strPrefix,strPrefixURI);

	if(ptrLibXMLLexer->getOptionalAttribute("xsi:type", strType)){ //TODO xsi getOptionalAttributeNS ??
		String strPrefix;
		String strTypeName;
		LibXMLLexer::ChopOffPrefix(strType, strPrefix, strTypeName);
		String strTypeURI;
		ptrLibXMLLexer->lookupURI(strPrefix,strTypeURI);
		pType = pDataFactory->getType(strTypeURI, strTypeName);

		if(pParent){
			pProperty = pParent->getType()->asComplexType()->getProperties().getProperty(strName);
		}

	}else{

		const DM::Type *pParentType = NULL;

		if(pParent==NULL){

			ptrLibXMLLexer->getPrefixWithURI(strPrefix,strPrefixURI);

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),"TEST Prefix:["<<strPrefix<<"]="<<strPrefixURI);

			pParentType=pDataFactory->getType(strPrefixURI,DM::DataFactory::RootTypeName);

		}else{
			pParentType=pParent->getType();
		}

		IAS_CHECK_IF_NULL(pParentType);

		pProperty = pParentType->asComplexType()->getProperties().getProperty(strName);

		pType = pProperty->getType();
	}

	DataObjectPtr ptrCurrent;

	bool bIsDataObject=pType->isDataObjectType();
	bool bIsEmpty=ptrLibXMLLexer->isEmpty();

	String strNIL;

	bool bIsNil = ptrLibXMLLexer->getOptionalAttribute("xsi:nil", strNIL) && strNIL.compare("true") == 0;

	if(bIsDataObject){

		if(bIsNil) {

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" : setNULL");

		}else{

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" : createEmpty");

			ptrCurrent = pType->createDataObject();

			while(ptrLibXMLLexer->nextAttribute()) {

				String strPrefix;
				String strPrefixUri;

				ptrLibXMLLexer->getPrefixWithURI(strPrefix, strPrefixUri);

				if(strPrefixUri.empty()) {
					String strName =ptrLibXMLLexer->getLocalName();
					IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Attr:"<<strName);
					String strValue =ptrLibXMLLexer->getValue();
					ptrCurrent->setString(strName,strValue);
				}
			}

		}

		//TODO verify
		if(!bIsEmpty)
			ptrLibXMLLexer->nextElement();

	}else{

		if(bIsNil) {

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" : setNULL");

		}else if(bIsEmpty){

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" : createEmpty");
			ptrCurrent = pType->createDataObject();

		}else{
			if(!ptrLibXMLLexer->nextElement())
				IAS_THROW(XMLHelperException(String("Value expected for: ")+=strName));

			if(ptrLibXMLLexer->checkType(XML_READER_TYPE_TEXT)){

					const char* sValue = ptrLibXMLLexer->getValue();

					IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),strName<<" : createFrom: ["<<sValue<<"]");
					ptrCurrent = pType->createDataObject(sValue);
					ptrLibXMLLexer->nextElement();

			}else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT)){
					IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),strName<<" : createEmpty");
					ptrCurrent = pType->createDataObject();
			}else{
				IAS_THROW(InternalException("Unhandled case in parse_xml_element()."));
			}


		}

	}

	if(pParent != NULL){

		IAS_CHECK_IF_NULL(pProperty);//slightly faster via property.
		if(!ptrCurrent.isNull() || !pXMLHelper->isSkipNullElements())
			pParent->setDataObject(pProperty,ptrCurrent);

	}else{

		ptrXMLDocument->setRootObject(ptrCurrent);
		ptrXMLDocument->setElement(strName);

		if(!strPrefixURI.empty())
			ptrXMLDocument->setURI(strPrefixURI);
		//TODO ptrXMLDocument->setEncoding() ??

	}

	//TODO why this line ?
	//DataObject* pCurrent = ptrCurrent.forget(); /* not an owner any more */
	DataObject* pCurrent = ptrCurrent.getPointer();

	if(bIsEmpty){
		//TODO - verify
		//ptrLibXMLLexer->nextElement();
		return;
	}

	do{

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_TEXT) && bIsDataObject){

			const char* sValue = ptrLibXMLLexer->getValue();

			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),strName<<" : createFrom: ["<<sValue<<"]"<<pType->getFullName());
			ptrCurrent->setString(XMLHelper::XMLPayloadElement,sValue);
			ptrLibXMLLexer->nextElement();
		}

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			   ptrLibXMLLexer->checkLocalName(strName))
				return;

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT)){
			if(!bIsDataObject)
				IAS_THROW(XMLHelperException(String("No elements expected for: ")+=strName));
			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" => start new child");
			parse_xml_element(pCurrent);
			IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),strName<<" <= finish  child");
		}

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException(String("At least close tag expected: ")+=strName));

	}while(true);
}
/*************************************************************************/
XMLDocument* XMLParser::parse(){
	IAS_TRACER;

	ptrLibXMLLexer->setSkipSignificantWhiteSpaces(true);

	ptrXMLDocument = IAS_DFT_FACTORY<XMLDocument>::Create();

	if( !ptrLibXMLLexer->nextElement() ||
		!ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT))
			IAS_THROW(XMLHelperException("Root element expected."))

	parse_xml_element(NULL);

	return ptrXMLDocument.pass();
}
/*************************************************************************/
}
}
}
