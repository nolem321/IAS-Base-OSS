/*
 * File: IAS-QSystemLib/src/qs/fmt/Parser.cpp
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
#include "Parser.h"
#include <qs/log/LogLevel.h>

#include <dm/xml/exception/XMLHelperException.h>
#include <dm/xml/LibXMLLexer.h>

#include <commonlib/commonlib.h>

#include <qs/api.h>

namespace IAS {
namespace QS {
namespace Fmt {

using namespace IAS::DM::XML;

/*************************************************************************/
Parser::Parser(DM::XML::XMLHelper* pXMLHelper, DM::XML::LibXMLLexer *pLibXMLLexer, QS::API::Attributes *pAttributes):
		XMLParser(pXMLHelper,pLibXMLLexer),
		pAttributes(pAttributes){

	IAS_TRACER;

	IAS_CHECK_IF_NULL(pDataFactory);

}
/*************************************************************************/
Parser::~Parser() throw(){
	IAS_TRACER;
}
/*************************************************************************/
void Parser::parse_soap_envelope(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Envelope");

	if(ptrLibXMLLexer->isEmpty()){
		IAS_THROW(XMLHelperException("Empty SOAP Envelope."));
	}

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Envelope: "<<ptrLibXMLLexer->getLocalName());

		if(ptrLibXMLLexer->checkLocalName("Header")){
			parse_soap_header();
		}else if(ptrLibXMLLexer->checkLocalName("Body")){
			parse_soap_body();
		} else if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("Envelope"))
			return;
	}

}
/*************************************************************************/
void Parser::parse_soap_header(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Header");

	if(ptrLibXMLLexer->isEmpty())
		return;

	while(true){

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
		   ptrLibXMLLexer->checkLocalName("Header"))
		return;
	}

}
/*************************************************************************/
void Parser::parse_soap_body(){
	IAS_TRACER;

	IAS_LOG(QS::LogLevel::INSTANCE.isInfo(),"SOAP Body");

	if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(DM::XML::XMLHelperException("Unexpected end of stream after soap:Body"));

	parse_xml_element(NULL);

	while(true){

		if(ptrLibXMLLexer->checkType(XML_READER_TYPE_END_ELEMENT) &&
			   ptrLibXMLLexer->checkLocalName("Body"))
		return;

		if(!ptrLibXMLLexer->nextElement())
			IAS_THROW(XMLHelperException("Unexpected end of xsd stream."))
	}

}
/*************************************************************************/
DM::XML::XMLDocument* Parser::parse(){

	IAS_TRACER;


	ptrLibXMLLexer->setSkipSignificantWhiteSpaces(true);

	ptrXMLDocument = IAS_DFT_FACTORY<DM::XML::XMLDocument>::Create();

	if( !ptrLibXMLLexer->nextElement() ||
		!ptrLibXMLLexer->checkType(XML_READER_TYPE_ELEMENT) ||
		String("Envelope").compare(ptrLibXMLLexer->getLocalName()) != 0)
			IAS_THROW(DM::XML::XMLHelperException("Root envelope element expected."))

	parse_soap_envelope();

	return ptrXMLDocument.pass();

}
/*************************************************************************/
}
}
}

/*************************************************************************/
