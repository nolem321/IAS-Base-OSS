/*
 * File: IAS-QSystemLib/src/qs/fmt/Serializer.cpp
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
#include "Serializer.h"
#include <qs/log/LogLevel.h>

#include <dm/xml/exception/XMLHelperException.h>
#include <dm/xml/LibXMLWriter.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

using namespace IAS::DM::XML;

/*************************************************************************/
Serializer::Serializer(DM::XML::XMLHelper* pXMLHelper, LibXMLWriter *pWriter, QS::API::Attributes *pAttributes):
		XMLSerializer(pXMLHelper,pWriter),
		pAttributes(pAttributes),
		pDocument(NULL){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
Serializer::~Serializer() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Serializer::write_soap_envelope(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Envelope");

	pWriter->startElementNS("soap","Envelope","http://www.w3.org/2003/05/soap-envelope");

	write_soap_header();
	write_soap_body();

	pWriter->endElement();

}
/*************************************************************************/
void Serializer::write_soap_header(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Header");

	pWriter->startElementNS("soap","Header","");

	if (pAttributes)
		if (pAttributes->isSet("IAS_SOAP_WSA_TO") || pAttributes->isSet("IAS_SOAP_WSA_ACTION")){
			pWriter->writeAttributeNS("xmlns","wsa","http://www.w3.org/2005/08/addressing","");

			if (pAttributes->isSet("IAS_SOAP_WSA_TO")) {
				pWriter->startElementNS("wsa","To","");
				pWriter->writeString(pAttributes->getValue("IAS_SOAP_WSA_TO"));
				pWriter->endElement();
			}

			if (pAttributes->isSet("IAS_SOAP_WSA_ACTION")) {
				pWriter->startElementNS("wsa","Action","");
				pWriter->writeString(pAttributes->getValue("IAS_SOAP_WSA_ACTION"));
				pWriter->endElement();
			}
		}

	pWriter->endElement();
}
/*************************************************************************/
void Serializer::write_soap_body(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Body");

	pWriter->startElementNS("soap","Body","");

	try{
		pRootObject=pDocument->getRootObject();
	}catch(ItemNotFoundException& e){
		IAS_THROW(XMLHelperException("RootObject for XMLDocument is missing."));
	}

	computeURI(pRootObject, true);

	const String& strElement(pDocument->getElement());
	const String& strElementURI(pDocument->getURI());

	//String strElementURI;

	bool bPrintTypeForRoot=true;

	//TODO test performance. tests show <+10%
	try{
		pDataFactory->getType(strElementURI,DM::DataFactory::RootTypeName)->asComplexType()->
				getProperties().getProperty(strElement);
		bPrintTypeForRoot=false;
	}catch(Exception& e){
		IAS_LOG(LogLevel::INSTANCE.isDetailedInfo(),"TODO Test:"<<e.toString());
	}catch(...){
		IAS_LOG(LogLevel::INSTANCE.isError(),"TODO something wrong");
	}

	if(!strElementURI.empty())
		addURI(strElementURI);

	serializeElement(pRootObject,pDocument->getElement(), bPrintTypeForRoot,strElementURI);

	pWriter->endElement();
}
/*************************************************************************/
void Serializer::serialize(const DM::XML::XMLDocument* pDocument){

	IAS_TRACER;

	pWriter->startDocument(pDocument->getVersion(),pDocument->getEncoding());


	this->pDocument=pDocument;
	write_soap_envelope();

	pWriter->endDocument();
}
/*************************************************************************/
}
}
}

/*************************************************************************/
