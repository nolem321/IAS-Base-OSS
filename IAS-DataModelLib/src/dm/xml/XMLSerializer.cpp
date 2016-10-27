/*
 * File: IAS-DataModelLib/src/dm/xml/XMLSerializer.cpp
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
#include "../../dm/xml/XMLSerializer.h"
#include <commonlib/commonlib.h>

#include "../../dm/DataFactory.h"
#include "../../dm/DataObject.h"
#include "../../dm/DataObjectList.h"
#include "../../dm/log/LogLevel.h"
#include "../../dm/Property.h"
#include "../../dm/PropertyList.h"
#include "../../dm/Type.h"
#include "../../dm/xml/exception/XMLHelperException.h"
#include "../../dm/xml/LibXMLWriterForFile.h"
#include "../../dm/xml/LibXMLWriterForMemory.h"
#include "../../dm/xml/XMLDocument.h"
#include "../../dm/xml/XMLHelper.h"

namespace IAS {
namespace DM {
namespace XML {


/*************************************************************************/
XMLSerializer::XMLSerializer(const XMLHelper* pXMLHelper, LibXMLWriter *pWriter):
				iCounter(0),
				pXMLHelper(pXMLHelper),
				pWriter(pWriter),
				pDataFactory(NULL),
				pRootObject(NULL){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pWriter);
	pDataFactory=pXMLHelper->getDataFactory();
}
/*************************************************************************/
XMLSerializer::~XMLSerializer() throw(){
	IAS_TRACER;

}
/*************************************************************************/
void XMLSerializer::addURI(const String& strURI){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isInfo(),pXMLHelper->isEmptyFirstNS());

	if(hmURI.count(strURI) == 0){
		char s[10];
		sprintf(s,"ns%d",iCounter++);

		if(hmURI.size() == 0 && pXMLHelper->isEmptyFirstNS())
			hmURI[strURI].clear();
		else
			hmURI[strURI]=s;

	}
}
/*************************************************************************/
const String& XMLSerializer::getURIPrefix(const String& strURI){
	IAS_TRACER;

	if(hmURI.count(strURI) == 0)
		IAS_THROW(InternalException(String("Missing: ")+strURI));
	return hmURI[strURI];
}
/*************************************************************************/
void XMLSerializer::listURIs(){
	IAS_TRACER;

	if(hmURI.size())
		pWriter->writeAttributeNS(String("xmlns"),"xsi","http://www.w3.org/2001/XMLSchema-instance",String(""));

	for(URIMap::iterator it = hmURI.begin();
			it != hmURI.end();
			it++){
		if(it->second.empty())
			pWriter->writeAttribute(String("xmlns"),it->first);
		else
			pWriter->writeAttributeNS(String("xmlns"),
					it->second.c_str(),
					it->first,
					String(""));
	}
}
/*************************************************************************/
void XMLSerializer::computeURI(DataObject* pDataObject,
								  bool        bAddURI){
	IAS_TRACER;

	const ::IAS::DM::Type* pType = pDataObject->getType();

	const String strURI(pDataObject->getType()->getURI());

	if((bAddURI || pXMLHelper->isPrefixElements()) && !strURI.empty())
		addURI(strURI);

	if(pType->isDataObjectType()){
		const ::IAS::DM::PropertyList &lstProperties = pType->asComplexType()->getProperties();
		for(int i=0; i<lstProperties.getSize(); i++){
			const Property* pProperty=lstProperties.getProperty(i);

			if(! pProperty->isMulti()){
					if(pDataObject->isSet(pProperty)){
						DataObject *pChild = pDataObject->getDataObject(pProperty);
						if(pChild)
							computeURI(pChild,! pChild->getType()->equals(pProperty->getType()));
					}/* IF:isSet */
			}else{

				DataObjectList& list = pDataObject->getList(pProperty);
				const String& strPropertyName = pProperty->getName();

				for(int j=0; j<list.size(); j++){
					DataObject *pChild = list.at(j);
					if(pChild)
						computeURI(pChild, ! pChild->getType()->equals(pProperty->getType()));
				}
			}/* IF: isMulti */

		}/*FOR:*/

	}/* IF: isDataType */

}
/*************************************************************************/
void XMLSerializer::serializeElement(const DataObject* pDataObject,
										 const String& strName,
										 bool  bXSIType,
										 const String& strURI){
	IAS_TRACER;

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Serialize["<<strName<<"]"<<(void*)pDataObject);

	if(!pDataObject && pXMLHelper->isSkipNullElements())
		return;

	/* Prefix */
	if(strURI.empty())
		pWriter->startElement(strName);
	else{
		const String& strURIPrefix(getURIPrefix(strURI));
		if(strURIPrefix.empty())
			pWriter->startElement(strName);
		else
			pWriter->startElementNS(getURIPrefix(strURI),strName,"");
	}


	if(!pDataObject){
		pWriter->writeAttribute("xsi:nil","true");
		pWriter->endElement();
		return;
	}

	if(pDataObject == pRootObject)
		listURIs();

	const ::IAS::DM::Type* pType = pDataObject->getType();

	/* xsi:type */
	if(bXSIType){
		String strAttrValue(getURIPrefix(pType->getURI()));
		if(!strAttrValue.empty())
			strAttrValue+=":";
		strAttrValue+=pType->getName();
		pWriter->writeAttributeNS(String("xsi"),String("type"),strAttrValue,String(""));
	}

	IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Enum:["<<pType->getTypeEnum()<<"]")

	switch(pType->getTypeEnum()){

		case ::IAS::DM::Type::BooleanType:
		case ::IAS::DM::Type::TextType:
		case ::IAS::DM::Type::IntegerType:
		case ::IAS::DM::Type::FloatType:
		case ::IAS::DM::Type::DateTimeType:
		case ::IAS::DM::Type::DateType:
		case ::IAS::DM::Type::TimeType:
			pWriter->writeString(pDataObject->toString());
		break;

		case ::IAS::DM::Type::AnyType:
		break;

		case ::IAS::DM::Type::DataObjectType:
		{
			const ::IAS::DM::PropertyList &lstProperties = pType->asComplexType()->getProperties();

			String strURI;

			if(pXMLHelper->isPrefixElements())
				strURI=pType->getURI();

			for(int i=0; i<lstProperties.getSize(); i++){

				const Property* pProperty=lstProperties.getProperty(i);
				if(pProperty->isXMLAttribute() && pDataObject->isSet(pProperty)){
					IAS_LOG(IAS::DM::LogLevel::INSTANCE.isDetailedInfo(),"Attribute["<<pProperty->getName()<<"]")
					pWriter->writeAttribute(pProperty->getName(),pDataObject->getDataObject(pProperty)->toString());
				}

			}

			for(int i=0; i<lstProperties.getSize(); i++){

				const Property* pProperty=lstProperties.getProperty(i);

				if(!pProperty->isXMLAttribute()){
					if(! pProperty->isMulti()){
						if(pDataObject->isSet(pProperty)){
							const DataObject *pChild = pDataObject->getDataObject(pProperty);
							const String& strPropertyName(pProperty->getName());

							if(strPropertyName.compare(XMLHelper::CXMLPayloadElement) == 0){
								pWriter->writeString(pDataObject->getString(XMLHelper::CXMLPayloadElement));
							}else
								serializeElement(pChild,
									         	 strPropertyName,
												 pChild && !pChild->getType()->equals(pProperty->getType()),
												 strURI);
						}/* IF: isSet */
					}else{

						const DataObjectList& list = pDataObject->getList(pProperty);
						const String& strPropertyName = pProperty->getName();

						for(int j=0; j<list.size(); j++){
							const DataObject *pChild = list.at(j);
							serializeElement(pChild,
											 strPropertyName,
											 pChild && !pChild->getType()->equals(pProperty->getType()),
											 strURI);
						}

					}

					}
				}/* FOR: */

				break;
			}
		default:
			IAS_THROW(InternalException("Not implemented DM Type in XMLSerializer."));
		}
	pWriter->endElement();
}
/*************************************************************************/
void XMLSerializer::serialize(const XMLDocument* pDocument){
	IAS_TRACER;
	IAS_CHECK_IF_VALID(pDocument);

	try{
		pRootObject=pDocument->getRootObject();
	}catch(ItemNotFoundException& e){
		IAS_THROW(XMLHelperException("RootObject for XMLDocument is missing."));
	}

	computeURI(pRootObject, true);

	pWriter->startDocument(pDocument->getVersion(),pDocument->getEncoding());

	const String& strElement(pDocument->getElement());
	const String& strElementURI(pDocument->getURI());

	//String strElementURI;

	bool bPrintTypeForRoot=true;

	//TODO test performance. tests show <+10%
	try{
		const DM::Property* pRootProperty = pDataFactory->getType(strElementURI,DM::DataFactory::RootTypeName)->asComplexType()->
				getProperties().getProperty(strElement);

		if(pRootProperty->getType() == pRootObject->getType()){
			bPrintTypeForRoot=false;
		}

	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"TODO Test:"<<e.toString());
	}catch(...){
		IAS_LOG(LogLevel::INSTANCE.isError(),"TODO something wrong");
	}

	if(!strElementURI.empty())
		addURI(strElementURI);

	serializeElement(pRootObject,pDocument->getElement(), bPrintTypeForRoot,strElementURI);
	pWriter->endDocument();
}

/*************************************************************************/
}
}
}
